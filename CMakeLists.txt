cmake_minimum_required(VERSION 3.22)
project(password_enc)

set(CMAKE_CXX_STANDARD 14)

# Include directory for Crypto++
include_directories(/usr/include/crypto++)

add_executable(password_enc
        encrypter.cpp
        encrypter.h
        main.cpp)

# Link against Crypto++ library
target_link_libraries(password_enc cryptopp)