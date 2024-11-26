#include "Speck.h"

#include <iostream>


void Speck::key_schedule(__uint128_t key) {
    auto left = static_cast<uint64_t>(key >> 64);
    auto right = static_cast<uint64_t>(key);
    keys[0] = static_cast<__uint128_t>(left) << 64 | right;
    for (int i = 1; i < rounds; ++i) {
        this->encrypt_round(keys[i], i);
    }
}

void Speck::encrypt(__uint128_t &block) {
    for (unsigned __int128 key: this->keys) {
        this->encrypt_round(block, key);
    }
}

void Speck::decrypt(__uint128_t &block) {
    for (int i = rounds - 1; i >= 0; --i) {
        this->decrypt_round(block, this->keys[i]);
    }
}

void Speck::encrypt_round(__uint128_t &block, __uint128_t key) {
    auto left = static_cast<uint64_t>(block >> 64);
    auto right = static_cast<uint64_t>(block);
    right = (right >> 8) | (right << (64 - 8));
    right += left;
    right ^= key;
    left = (left << 3) | (left >> (64 - 3));
    left ^= right;
    block = (static_cast<__uint128_t>(left) << 64) | right;
}

void Speck::decrypt_round(__uint128_t &block, __uint128_t key) {
    auto right = static_cast<uint64_t>(block);
    auto left = static_cast<uint64_t>(block >> 64);

    left ^= right;
    left = (left >> 3) | (left << (64 - 3));
    right ^= key;
    right -= left;
    right = (right << 8) | (right >> (64 - 8));

    block = (static_cast<__uint128_t>(left) << 64) | right;
}

void Speck::encrypt_file(const std::string &input_file, const std::string &output_file) {
    std::ifstream infile(input_file, std::ios::binary);
    std::ofstream outfile(output_file, std::ios::binary);
    if (!infile.is_open() || !outfile.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла.");
    }

    std::vector<char> buffer(16);
    while (infile.read(buffer.data(), buffer.size())) {
        __uint128_t block = *reinterpret_cast<__uint128_t *>(buffer.data());
        encrypt(block);
        outfile.write(reinterpret_cast<char *>(&block), sizeof(block));
    }

    if (infile.gcount() > 0) {
        buffer.resize(infile.gcount());
        infile.read(buffer.data(), buffer.size());
        __uint128_t block = 0;
        std::ranges::copy(buffer, reinterpret_cast<char *>(&block));
        encrypt(block);
        outfile.write(reinterpret_cast<char *>(&block), sizeof(block));
    }

    infile.close();
    outfile.close();
}


void Speck::decrypt_file(const std::string &input_file, const std::string &output_file) {
    std::ifstream infile(input_file, std::ios::binary);
    std::ofstream outfile(output_file, std::ios::binary);
    if (!infile.is_open() || !outfile.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла.");
    }

    std::vector<char> buffer(16);
    while (infile.read(buffer.data(), buffer.size())) {
        __uint128_t block = *reinterpret_cast<__uint128_t *>(buffer.data());
        decrypt(block);
        outfile.write(reinterpret_cast<char *>(&block), sizeof(block));
    }

    if (infile.gcount() > 0) {
        buffer.resize(infile.gcount());
        infile.read(buffer.data(), buffer.size());
        __uint128_t block = 0;
        std::ranges::copy(buffer, reinterpret_cast<char *>(&block));
        decrypt(block);
        outfile.write(reinterpret_cast<char *>(&block), sizeof(block));
    }

    infile.close();
    outfile.close();
}
