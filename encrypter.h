#include <cryptopp/aes.h>
#include <cryptopp/default.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

class Encrypter {
 private:
  CryptoPP::SecByteBlock key;
  CryptoPP::SecByteBlock iv;
 public:
  Encrypter(const std::string& keyStr);
  std::string encrypt(const std::string& plainText);
  std::string decrypt(const std::string& cipherText);
};