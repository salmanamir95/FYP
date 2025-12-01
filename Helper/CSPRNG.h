#pragma once
#include <cstdint>
#include <openssl/rand.h>
#include <stdexcept>

inline uint16_t CSPRNG16_t() {
    uint16_t randomNumber;

    // Generate 2 bytes of cryptographically secure random data
    if (RAND_bytes(reinterpret_cast<unsigned char*>(&randomNumber), sizeof(randomNumber)) != 1) {
        throw std::runtime_error("CSPRNG2_t: RAND_bytes failed");
    }

    return randomNumber;
}

inline uint64_t CSPRNG64_t() {
    uint64_t randomNumber;

    // Generate 8 bytes of cryptographically secure random data
    if (RAND_bytes(reinterpret_cast<unsigned char*>(&randomNumber), sizeof(randomNumber)) != 1) {
        throw std::runtime_error("CSPRNG2_t: RAND_bytes failed");
    }

    return randomNumber;
}