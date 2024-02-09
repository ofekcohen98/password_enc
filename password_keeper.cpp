//
// Created by ofekc on 08/02/2024.
//

#include "password_keeper.h"
#include "encrypter.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include </usr/local/include/json.hpp>
#include <string> // Include this for std::string
#include <cstdlib> // Include this for getenv()


#define ENV_FILE_PATH "/home/ofekcohen/clion/password_enc/.env"


using json = nlohmann::json;

Password_keeper::Password_keeper() {
  // Load JSON file names from .env file
  loadEnvVariables(ENV_FILE_PATH);
  writeToJson();
  writeTousers();
}

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

void Password_keeper::writeToJson() {
  std::string filePath = path +"/"+ passJsonFileName;
  std::ifstream fileCheck(filePath);
  if (fileCheck.good()) {
    std::cout << "File already exists: " << filePath << std::endl;
    return; // Exit the function if the file already exists
  }
  fileCheck.close(); // Close the file stream
  // Create an empty JSON object
  json passData;

  // Write the empty JSON object to the passwords.json file
  std::ofstream passOfs(filePath);
  if (passOfs.is_open()) {
    passOfs << std::setw(4) << passData << std::endl;
    passOfs.close();
    std::cout << "File created: " << filePath << std::endl;
  } else {
    std::cerr << "Failed to create file: " << filePath << std::endl;
  }
}

void Password_keeper::writeTousers() {
  std::string filePath = path +"/"+ usersJsonFileName;
  std::ifstream fileCheck(filePath);
  if (fileCheck.good()) {
    std::cout << "File already exists: " << filePath << std::endl;
    return; // Exit the function if the file already exists
  }
  fileCheck.close(); // Close the file stream
  // Create an empty JSON object
  json passData;

  // Write the empty JSON object to the passwords.json file
  std::ofstream passOfs(filePath);
  if (passOfs.is_open()) {
    passOfs << std::setw(4) << passData << std::endl;
    passOfs.close();
    std::cout << "File created: " << filePath << std::endl;
  } else {
    std::cerr << "Failed to create file: " << filePath << std::endl;
  }
}