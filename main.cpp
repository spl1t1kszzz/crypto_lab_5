#include <iostream>
#include <string>

#include "LCG/LCG.h"
#include "MurmurHash2/murmurhash2.h"
#include "Speck/Speck.h"


std::string xor_encrypt_decrypt(const std::string &text, const std::string &key) {
    std::string result;
    for (size_t i = 0; i < text.size(); ++i) {
        result += static_cast<char>(key[i] ^ text[i]);
    }
    return result;
}


int main() {
    std::string text;
    constexpr unsigned int seed = 1;
    std::getline(std::cin, text);
    LCG lcg(seed);
    std::string key;
    for (size_t i = 0; i < text.size(); ++i) {
        key += lcg.next();
    }
    const std::string encrypted_text = xor_encrypt_decrypt(text, key);
    std::cout << "Зашифрованный текст: " << encrypted_text << std::endl;
    const std::string decrypted_text = xor_encrypt_decrypt(encrypted_text, key);
    std::cout << "Дешифрованный текст: " << decrypted_text << std::endl;
    const __uint128_t speck_key = (static_cast<__uint128_t>(0x0123456789ABCDEF) << 64) | 0xFEDCBA9876543210;
    Speck speck(speck_key);
    try {
        speck.encrypt_file("input.txt", "out.txt");
        speck.decrypt_file("out.txt", "res.txt");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "Murmurhash2 for " << text << " is " << murmur_hash2(text) << std::endl;
    return 0;
}
