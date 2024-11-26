#ifndef MURMURHASH2_H
#define MURMURHASH2_H
#include <iostream>
#include <string>
#include <cstdint>

uint32_t murmur_hash2(const std::string &key, uint32_t seed = 0);


#endif
