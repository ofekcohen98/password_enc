#include "encrypter.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include </usr/local/include/json.hpp>
#include <string> // Include this for std::string
#include <cstdlib> // Include this for getenv()
#define ENV_FILE_PATH "/home/ofekcohen/clion/password_enc/.env"


using json = nlohmann::json;


class Password_keeper {
 private:
  nlohmann::json users;
  nlohmann::json passwords;
  Encrypter& encrypter;
  std::string passJsonFileName;
  std::string usersJsonFileName;
  std::string path;

  void loadUsers();
  void saveUsers();
  void loadPasswords();
  void savePasswords();

 public:

  Password_keeper(Encrypter& encrypter);
  void loadEnvVariables(const std::string& filename);
  void storeUser(const std::string& username, const std::string& password);
  bool authenticateUser(const std::string& username, const std::string& password);
  void storePassword(const std::string& username, const std::string& site, const std::string& password);
  std::string retrievePassword(const std::string& username, const std::string& site);
  void deletePassword(const std::string& username, const std::string& site);
  std::string getPassJsonFileName() const;

  // Setter for passJsonFileName
  void setPassJsonFileName(const std::string& value);

  // Getter for usersJsonFileName
  std::string getUsersJsonFileName() const;

  // Setter for usersJsonFileName
  void setUsersJsonFileName(const std::string& value);

  // Getter for path
  std::string getPath() const;

  // Setter for path
  void setPath(const std::string& value);
};