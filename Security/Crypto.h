#pragma once
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

// Compute SHA256 hash of public key DER and return hex string
std::string ComputePublicKeyHash(EVP_PKEY* pkey) {
    unsigned char* der = nullptr;
    int derLen = i2d_PUBKEY(pkey, &der);
    if (derLen <= 0) return "";

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(der, derLen, hash);
    OPENSSL_free(der);

    std::string hexHash;
    char buf[3];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(buf, "%02x", hash[i]);
        hexHash += buf;
    }
    return hexHash;
}

// Check if hash exists in log file
bool HashExistsInLog(const std::string& logFile, const std::string& hash) {
    std::ifstream infile(logFile);
    if (!infile.is_open()) return false;

    std::string line;
    while (std::getline(infile, line)) {
        if (line == hash) return true;
    }
    return false;
}

// Append hash to log
void AppendHashToLog(const std::string& logFile, const std::string& hash) {
    std::ofstream outfile(logFile, std::ios::app);
    outfile << hash << "\n";
}

// Generate X25519 key pair, store PEMs, maintain hash log, retry if collision
bool GenerateAndLogX25519Key(uint32_t node_id) {
    fs::path keyDir = fs::current_path() / "EncryptionKeys";
    if (!fs::exists(keyDir)) fs::create_directory(keyDir);

    std::string privFile = (keyDir / (std::to_string(node_id) + "_private.pem")).string();
    std::string pubFile  = (keyDir / (std::to_string(node_id) + "_public.pem")).string();
    std::string logFile  = (keyDir / (std::to_string(node_id) + "_keys_log.log")).string();

    // Ensure log file exists
    if (!fs::exists(logFile)) {
        std::ofstream(logFile).close();
    }

    // Delete existing key files
    if (fs::exists(privFile)) fs::remove(privFile);
    if (fs::exists(pubFile))  fs::remove(pubFile);

    bool success = false;

    while (!success) {
        // Generate X25519 key
        EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_X25519, nullptr);
        if (!ctx) return false;
        if (EVP_PKEY_keygen_init(ctx) <= 0) { EVP_PKEY_CTX_free(ctx); return false; }

        EVP_PKEY* pkey = nullptr;
        if (EVP_PKEY_keygen(ctx, &pkey) <= 0) { EVP_PKEY_CTX_free(ctx); return false; }
        EVP_PKEY_CTX_free(ctx);

        // Compute public key hash
        std::string pubHash = ComputePublicKeyHash(pkey);
        if (pubHash.empty()) { EVP_PKEY_free(pkey); return false; }

        // Check for duplicates in log
        if (HashExistsInLog(logFile, pubHash)) {
            std::cerr << "Duplicate key detected! Retrying..." << std::endl;
            EVP_PKEY_free(pkey);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        // Save private key PEM
        FILE* privFp = fopen(privFile.c_str(), "wb");
        if (!privFp) { EVP_PKEY_free(pkey); return false; }
        if (!PEM_write_PrivateKey(privFp, pkey, nullptr, nullptr, 0, nullptr, nullptr)) {
            fclose(privFp); EVP_PKEY_free(pkey); return false;
        }
        fclose(privFp);

        // Save public key PEM
        FILE* pubFp = fopen(pubFile.c_str(), "wb");
        if (!pubFp) { EVP_PKEY_free(pkey); return false; }
        if (!PEM_write_PUBKEY(pubFp, pkey)) {
            fclose(pubFp); EVP_PKEY_free(pkey); return false;
        }
        fclose(pubFp);

        // Append hash to log
        AppendHashToLog(logFile, pubHash);

        std::cout << "Node X25519 key pair generated and logged successfully!" << std::endl;

        EVP_PKEY_free(pkey);
        success = true;
    }

    return true;
}


EVP_PKEY* LoadPrivateKey(uint32_t node_id) {
    fs::path keyPath = fs::current_path() / "EncryptionKeys" / (std::to_string(node_id) + "_private.pem");
    if (!fs::exists(keyPath)) {
        std::cerr << "Private key file not found: " << keyPath << std::endl;
        return nullptr;
    }

    FILE* privFile = fopen(keyPath.string().c_str(), "rb");
    if (!privFile) {
        std::cerr << "Failed to open private key file: " << keyPath << std::endl;
        return nullptr;
    }

    EVP_PKEY* pkey = PEM_read_PrivateKey(privFile, nullptr, nullptr, nullptr);
    fclose(privFile);

    if (!pkey) {
        std::cerr << "Failed to read private key from PEM: " << keyPath << std::endl;
        return nullptr;
    }

    return pkey; // Caller must free with EVP_PKEY_free()
}

// Load public key from PEM file
EVP_PKEY* LoadPublicKey(uint32_t node_id) {
    fs::path keyPath = fs::current_path() / "EncryptionKeys" / (std::to_string(node_id) + "_public.pem");
    if (!fs::exists(keyPath)) {
        std::cerr << "Public key file not found: " << keyPath << std::endl;
        return nullptr;
    }

    FILE* pubFile = fopen(keyPath.string().c_str(), "rb");
    if (!pubFile) {
        std::cerr << "Failed to open public key file: " << keyPath << std::endl;
        return nullptr;
    }

    EVP_PKEY* pkey = PEM_read_PUBKEY(pubFile, nullptr, nullptr, nullptr);
    fclose(pubFile);

    if (!pkey) {
        std::cerr << "Failed to read public key from PEM: " << keyPath << std::endl;
        return nullptr;
    }

    return pkey; // Caller must free with EVP_PKEY_free()
}

std::vector<unsigned char> SharedSecretKeyGen(uint32_t node_id, EVP_PKEY* peerPublicKey) {
    std::vector<unsigned char> sharedSecret;

    // Load the node's private key
    EVP_PKEY* privateKey = LoadPrivateKey(node_id);
    if (!privateKey) {
        std::cerr << "Failed to load private key for node " << node_id << std::endl;
        return sharedSecret;
    }

    // Create derivation context
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(privateKey, nullptr);
    if (!ctx) {
        std::cerr << "Failed to create EVP_PKEY_CTX" << std::endl;
        EVP_PKEY_free(privateKey);
        return sharedSecret;
    }

    if (EVP_PKEY_derive_init(ctx) <= 0) {
        std::cerr << "EVP_PKEY_derive_init failed" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(privateKey);
        return sharedSecret;
    }

    if (EVP_PKEY_derive_set_peer(ctx, peerPublicKey) <= 0) {
        std::cerr << "EVP_PKEY_derive_set_peer failed" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(privateKey);
        return sharedSecret;
    }

    // Determine required buffer length
    size_t secretLen = 0;
    if (EVP_PKEY_derive(ctx, nullptr, &secretLen) <= 0) {
        std::cerr << "EVP_PKEY_derive failed to get length" << std::endl;
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(privateKey);
        return sharedSecret;
    }

    sharedSecret.resize(secretLen);

    // Derive shared secret
    if (EVP_PKEY_derive(ctx, sharedSecret.data(), &secretLen) <= 0) {
        std::cerr << "EVP_PKEY_derive failed" << std::endl;
        sharedSecret.clear();
    } else {
        sharedSecret.resize(secretLen);
    }

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(privateKey);

    return sharedSecret; // raw bytes
}

bool Encrypt(
    uint32_t senderNodeID,
    EVP_PKEY* receiverPublicKey,
    const std::vector<unsigned char>& message,
    std::vector<unsigned char>& ciphertext,
    std::vector<unsigned char>& iv,
    std::vector<unsigned char>& tag
) {
    // Step 1: Generate shared secret
    std::vector<unsigned char> sharedSecret = SharedSecretKeyGen(senderNodeID, receiverPublicKey);
    if (sharedSecret.empty()) {
        std::cerr << "Failed to generate shared secret" << std::endl;
        return false;
    }

    // Step 2: Generate cryptographically secure IV
    try {
        iv = GenerateIV(12); // 12-byte IV for AES-GCM
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    // Step 3: Encrypt message using AES-GCM with shared secret
    if (!AESGCMEncrypt(sharedSecret, message, ciphertext, iv, tag)) {
        std::cerr << "AES-GCM encryption failed" << std::endl;
        return false;
    }

    return true;
}

bool Decrypt(
    uint32_t receiverNodeID,
    EVP_PKEY* senderPublicKey,
    const std::vector<unsigned char>& ciphertext,
    const std::vector<unsigned char>& iv,
    const std::vector<unsigned char>& tag,
    std::vector<unsigned char>& plaintext
) {
    // Step 1: Derive shared secret using receiver private key + sender public key
    std::vector<unsigned char> sharedSecret = SharedSecretKeyGen(receiverNodeID, senderPublicKey);
    if (sharedSecret.empty()) {
        std::cerr << "Failed to generate shared secret" << std::endl;
        return false;
    }

    // Step 2: Decrypt ciphertext using AES-GCM
    if (!AESGCMDecrypt(sharedSecret, ciphertext, iv, tag, plaintext)) {
        std::cerr << "AES-GCM decryption failed or authentication failed" << std::endl;
        return false;
    }

    return true;
}