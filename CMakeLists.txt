cmake_minimum_required(VERSION 3.22)
project(password_enc)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/share/doc/libboost-all-dev)

add_executable(password_enc
        encrypter.cpp
        encrypter.h
        main.cpp
        password_keeper.cpp
        password_keeper.h)

# Link against Crypto++ library
target_link_libraries(password_enc cryptopp)