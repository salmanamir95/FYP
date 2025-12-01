#include <vector>
#include <cstdint>
#include <openssl/sha.h>
using namespace std;
vector<uint8_t> sha256(const std::vector<uint8_t>& data) {
    vector<uint8_t> hash(SHA256_DIGEST_LENGTH); // 32 bytes

    // Compute SHA-256
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, data.data(), data.size());
    SHA256_Final(hash.data(), &ctx);

    return hash; // returns 32-byte SHA-256 hash
}
