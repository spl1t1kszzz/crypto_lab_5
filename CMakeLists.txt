cmake_minimum_required(VERSION 3.28)
project(crypto_lab_5)

set(CMAKE_CXX_STANDARD 20)

add_executable(crypto_lab_5 main.cpp
        LCG/LCG.h
        LCG/LCG.cpp
        Speck/Speck.h
        Speck/Speck.cpp
        MurmurHash2/murmurhash2.cpp
        MurmurHash2/murmurhash2.h)
