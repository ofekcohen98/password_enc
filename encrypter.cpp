//
// Created by ofekc on 08/02/2024.
//

#include "encrypter.h"
#include <string>

std::string Encrypter::encrypt(const std::string& plaintext) {
  CryptoPP::AES::Encryption aesEncryption((CryptoPP::byte*)master_key.c_str()
                                          , CryptoPP::AES::DEFAULT_KEYLENGTH);
  CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (CryptoPP::byte*)master_key.c_str());

  std::string ciphertext;
  CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
  stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length() + 1);
  stfEncryptor.MessageEnd();

  return ciphertext;
}

std::string Encrypter::decrypt(const std::string& ciphertext) {
  CryptoPP::AES::Decryption aesDecryption((CryptoPP::byte*)master_key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
  CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (CryptoPP::byte*)master_key.c_str());

  std::string decryptedtext;
  CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
  stfDecryptor.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
  stfDecryptor.MessageEnd();

  return decryptedtext;
}