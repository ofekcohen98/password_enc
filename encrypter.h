//
// Created by ofekc on 08/02/2024.
//
#ifndef ENCRYPTER_H
#define ENCRYPTER_H

#include <string>
#include </usr/include/crypto++/aes.h>
#include </usr/include/crypto++/modes.h>
#include </usr/include/crypto++/filters.h>

class Encrypter {
 private:
  std::string master_key;

 public:
  Encrypter(std::string key): master_key(key) {}
  std::string encrypt(const std::string& plaintext);
  std::string decrypt(const std::string& ciphertext);
};

#endif // ENCRYPTER_H