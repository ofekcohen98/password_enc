//
// Created by ofekc on 08/02/2024.
//

#ifndef _PASSWORD_KEEPER_H_
#define _PASSWORD_KEEPER_H_
#include <string>
class Password_keeper
{
 private:
  std::string passJsonFileName;
  std::string usersJsonFileName;
  std::string path;

 public:
  Password_keeper();
  void writeToJson();
  void loadEnvVariables(const std::string& filename);
  void writeTousers();
};


#endif //_PASSWORD_KEEPER_H_
