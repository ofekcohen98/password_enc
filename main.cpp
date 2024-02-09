//
// Created by ofekc on 08/02/2024.
//

#include "encrypter.h"
#include "password_keeper.h"
#include <iostream>

int main() {
//  Password_keeper keeper;
  Encrypter encrypter("hey");
  std::string enc = encrypter.encrypt("Ruth078");
  std::cout << enc<<"\n";
  std::string dec = encrypter.decrypt(enc);
  std::cout <<dec;

  return 0;
}
