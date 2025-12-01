#pragma once
#include<thread>
#include <vector>
#include <array>
#include <cstdint>
#include <ctime>
#include <arpa/inet.h> // for htons, htonl
#include <Blockchain/PKCertChain/nodeReg.h>
#include <Consensus/PowChallenge.h>
using namespace std;

// ----------- Runtime Endian Detection -----------

inline bool isLittleEndian() {
    uint16_t x = 1;
    return *reinterpret_cast<uint8_t*>(&x) == 1;
}

// ----------- Endian conversions -----------

// 16-bit BE
inline vector<uint8_t> BE16(uint16_t num) {
    if (isLittleEndian()) num = htons(num);
    return { static_cast<uint8_t>(num >> 8), static_cast<uint8_t>(num & 0xFF) };
}

// 32-bit BE
inline vector<uint8_t> BE32(uint32_t num) {
    if (isLittleEndian()) num = htonl(num);
    return {
        static_cast<uint8_t>((num >> 24) & 0xFF),
        static_cast<uint8_t>((num >> 16) & 0xFF),
        static_cast<uint8_t>((num >> 8) & 0xFF),
        static_cast<uint8_t>(num & 0xFF)
    };
}

// 64-bit BE
inline uint64_t htonll(uint64_t value) {
    if (isLittleEndian()) {
        return ((uint64_t)htonl(value & 0xFFFFFFFF) << 32) | htonl(value >> 32);
    } else {
        return value;
    }
}

inline vector<uint8_t> BE64(uint64_t num) {
    num = htonll(num);
    vector<uint8_t> bytes(8);
    for (int i = 0; i < 8; i++) {
        bytes[i] = static_cast<uint8_t>((num >> (56 - i * 8)) & 0xFF);
    }
    return bytes;
}

// time_t BE (assumes time_t <= 64-bit)
inline vector<uint8_t> BE_time(time_t t) {
    return BE64(static_cast<uint64_t>(t));
}

// ----------- Serialization -----------

// Serialize a certificate
inline vector<uint8_t> serializeCertificate(const certificate& cert) {
    vector<uint8_t> bytes;

    // nodeID
    vector<uint8_t> nid = BE16(cert.nodeID);
    bytes.insert(bytes.end(), nid.begin(), nid.end());

    // publicKey
    bytes.insert(bytes.end(), cert.publicKey.begin(), cert.publicKey.end());

    // signature
    bytes.insert(bytes.end(), cert.signature.begin(), cert.signature.end());

    // notBefore, notAfter
    vector<uint8_t> nb = BE_time(cert.notBefore);
    vector<uint8_t> na = BE_time(cert.notAfter);
    bytes.insert(bytes.end(), nb.begin(), nb.end());
    bytes.insert(bytes.end(), na.begin(), na.end());

    return bytes;
}

// Serialize a nodeReg (excluding pointers)
inline vector<uint8_t> serializeNode(const nodeReg& node) {
    vector<uint8_t> bytes;

    // prevHash, nextHash, blockHash
    bytes.insert(bytes.end(), node.prevHash.begin(), node.prevHash.end());
    bytes.insert(bytes.end(), node.nextHash.begin(), node.nextHash.end());
    bytes.insert(bytes.end(), node.blockHash.begin(), node.blockHash.end());

    // nonce (serialize length first)
    uint64_t nonceSize = node.nonce.size();
    vector<uint8_t> nonceSizeBE = BE64(nonceSize);
    bytes.insert(bytes.end(), nonceSizeBE.begin(), nonceSizeBE.end());
    bytes.insert(bytes.end(), node.nonce.begin(), node.nonce.end());

    // difficulty
    vector<uint8_t> diff = BE16(node.difficulty);
    bytes.insert(bytes.end(), diff.begin(), diff.end());

    // timestamp
    vector<uint8_t> ts = BE_time(node.timestamp);
    bytes.insert(bytes.end(), ts.begin(), ts.end());

    // certificate
    vector<uint8_t> certBytes = serializeCertificate(node.cert);
    bytes.insert(bytes.end(), certBytes.begin(), certBytes.end());

    return bytes;
}

inline vector<uint8_t> serializePowChallenge(const PowChallenge& chal) {
    vector<uint8_t> bytes;
    
    // Append R (32 bytes)
    bytes.insert(bytes.end(), chal.challenge.begin(), chal.challenge.end());

    // Append T (2 bytes)
    bytes.insert(bytes.end(), chal.difficulty.begin(), chal.difficulty.end());

    return bytes;
}
