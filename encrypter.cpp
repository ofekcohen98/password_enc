#include "encrypter.h"
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#define BLOCK ""

Encrypter::Encrypter(const std::string& keyStr) {
  std::string keyData = keyStr;
  if (keyData.size() < 16) {
    keyData.append(16 - keyData.size(), '\0');
  } else if (keyData.size() > 16 && keyData.size() < 24) {
    keyData = keyData.substr(0, 16);
  } else if (keyData.size() > 24 && keyData.size() < 32) {
    keyData = keyData.substr(0, 24);
  } else if (keyData.size() > 32) {
    keyData = keyData.substr(0, 32);
  }
  key = CryptoPP::SecByteBlock((const unsigned char*)(keyData.data()), keyData.size());
  // Generate IV from keyStr
  CryptoPP::SHA256 hash;
  CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
  hash.CalculateDigest(digest, (CryptoPP::byte*)keyStr.c_str(), keyStr.length());
  iv = CryptoPP::SecByteBlock(digest, CryptoPP::AES::BLOCKSIZE);
}

std::string Encrypter::encrypt(const std::string& plainText) {
  try {
    std::string cipherText, encoded;
    CryptoPP::AutoSeededRandomPool prng;

    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(key, key.size(), iv);
    CryptoPP::StringSource ss1(plainText, true,
                               new CryptoPP::StreamTransformationFilter(cfbEncryption,
                                                                        new CryptoPP::StringSink(cipherText)
                               ) // StreamTransformationFilter
    ); // StringSource

    // Base64 encode
    CryptoPP::StringSource ss2(cipherText, true,
                               new CryptoPP::Base64Encoder(
                                   new CryptoPP::StringSink(encoded)
                               ) // Base64Encoder
    ); // StringSource

    return encoded;
  } catch (const CryptoPP::Exception& e) {
    // Handle the exception
    std::cerr << e.what() << std::endl;
    return BLOCK;
  }
}

std::string Encrypter::decrypt(const std::string& cipherText) {
  try {
    std::string decoded, decryptedText;
    CryptoPP::AutoSeededRandomPool prng;

    // Base64 decode
    CryptoPP::StringSource ss1(cipherText, true,
                               new CryptoPP::Base64Decoder(
                                   new CryptoPP::StringSink(decoded)
                               ) // Base64Decoder
    ); // StringSource

    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption(key, key.size(), iv);
    CryptoPP::StringSource ss2(decoded, true,
                               new CryptoPP::StreamTransformationFilter(cfbDecryption,
                                                                        new CryptoPP::StringSink(decryptedText)
                               ) // StreamTransformationFilter
    ); // StringSource

    return decryptedText;
  } catch (const CryptoPP::Exception& e) {
    // Handle the exception
    std::cerr << e.what() << std::endl;
    return BLOCK;
  }
}