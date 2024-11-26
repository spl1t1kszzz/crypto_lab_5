#ifndef SPECK_H
#define SPECK_H
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

class Speck {
public:
    explicit Speck(__uint128_t key) {
        key_schedule(key);
    }

    void encrypt(__uint128_t &block);
    void decrypt(__uint128_t &block);

    void encrypt_file(const std::string& input_file, const std::string& output_file);
    void decrypt_file(const std::string& input_file, const std::string& output_file);

private:
    static const int rounds = 32;
    __uint128_t keys[rounds]{};

    static void encrypt_round(__uint128_t &block, __uint128_t key);
    static void decrypt_round(__uint128_t &block, __uint128_t key);

    void key_schedule(__uint128_t key);
};


#endif
