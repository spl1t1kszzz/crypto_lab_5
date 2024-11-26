#include "murmurhash2.h"

uint32_t murmur_hash2(const std::string &key, uint32_t seed) {
    constexpr uint32_t m = 0x5bd1e995;

    uint32_t len = key.size();
    uint32_t h = seed ^ len;

    const auto *data = reinterpret_cast<const unsigned char *>(key.data());
    while (len >= 4) {
        constexpr int r = 24;
        uint32_t k = *reinterpret_cast<const uint32_t *>(data);
        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
        default: ;
    }

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}
