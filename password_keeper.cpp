#include "password_keeper.h"

void Password_keeper::loadEnvVariables(const std::string& filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::map<std::string, std::string> envVariables;
    std::string line;
    while (std::getline(file, line)) {
      size_t delimiterPos = line.find('=');
      if (delimiterPos != std::string::npos) {
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        envVariables[key] = value;
      }
    }
    // Set passJsonFileName and usersJsonFileName if found in .env file
    if (envVariables.count("PASS_JSON_FILE_NAME")) {
      passJsonFileName = envVariables["PASS_JSON_FILE_NAME"];
    } else {
      std::cerr << "PASS_JSON_FILE_NAME not found in .env file. Using default value: passwords.json" << std::endl;
      passJsonFileName = "passwords.json";
    }

    if (envVariables.count("USERS_JSON_FILE_NAME")) {
      usersJsonFileName = envVariables["USERS_JSON_FILE_NAME"];
    } else {
      std::cerr << "USERS_JSON_FILE_NAME not found in .env file. Using default value: users.json" << std::endl;
      usersJsonFileName = "users.json";
    }
    if (envVariables.count("PATH")) {
      path = envVariables["PATH"];
    } else {
      std::cerr << "path not found in .env file. Using default value: "<<
                "/home/ofekcohen/clion/password_enc";
      path = "/home/ofekcohen/clion/password_enc";
    }

    file.close();
  } else {
    std::cerr << "Failed to open .env file." << std::endl;
  }
}

Password_keeper::Password_keeper(Encrypter& encrypter): encrypter(encrypter) {
  loadEnvVariables(ENV_FILE_PATH);
  loadUsers();
  loadPasswords();
}

void Password_keeper::loadUsers() {
  std::string usersFileName = path + "/" + usersJsonFileName;
  std::ifstream usersFile(usersFileName);
  usersFile >> users;
  usersFile.close();
}

void Password_keeper::saveUsers() {
  std::string usersFileName = path + "/" + usersJsonFileName;
  std::ofstream usersFile(usersFileName);
  usersFile << users;
  usersFile.close();
}

void Password_keeper::loadPasswords() {
  std::string passFileName = path + "/" + passJsonFileName;
  std::ifstream passwordsFile(passFileName);
  passwordsFile >> passwords;
  passwordsFile.close();
  }

void Password_keeper::savePasswords() {
  std::string passFileName = path + "/" + passJsonFileName;
  std::ofstream passwordsFile(passFileName);
  passwordsFile << passwords;
  passwordsFile.close();
}

void Password_keeper::storeUser(const std::string& username, const std::string& password) {
  std::string encryptedPassword = encrypter.encrypt(password);
  users[username] = encryptedPassword;
  saveUsers();
}

bool Password_keeper::authenticateUser(const std::string& username, const std::string& password) {
  if(users.find(username) != users.end()) {
    std::string encryptedPassword = users[username];
    return encrypter.decrypt(encryptedPassword) == password;
  } else {
    return false;
  }
}

void Password_keeper::storePassword(const std::string& username, const std::string& site, const std::string& password) {
  std::string encryptedPassword = encrypter.encrypt(password);
  passwords[username][site] = encryptedPassword;
  savePasswords();
}

void Password_keeper::deletePassword(const std::string& username, const std::string& site) {
  if (passwords.find(username) != passwords.end()) {
    if (passwords[username].find(site) != passwords[username].end()) {
      passwords[username].erase(site);
      savePasswords();
    } else {
      std::cout << "No password stored for this site." << std::endl;
    }
  } else {
    std::cout << "No user found." << std::endl;
  }
}

std::string Password_keeper::retrievePassword(const std::string& username, const std::string& site) {
  if(passwords.find(username) != passwords.end() && passwords[username].find(site) != passwords[username].end()) {
    std::string encryptedPassword = passwords[username][site];
    return encrypter.decrypt(encryptedPassword);
  } else {
    return "";
  }
}

std::string Password_keeper::getPassJsonFileName() const {
  return passJsonFileName;
}

void Password_keeper::setPassJsonFileName(const std::string& value) {
  passJsonFileName = value;
}

std::string Password_keeper::getUsersJsonFileName() const {
  return usersJsonFileName;
}

void Password_keeper::setUsersJsonFileName(const std::string& value) {
  usersJsonFileName = value;
}

std::string Password_keeper::getPath() const {
  return path;
}

void Password_keeper::setPath(const std::string& value) {
  path = value;
}