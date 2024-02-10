#include <iostream>
#include "password_keeper.h"
#include <cassert>
void testEncrypter(const std::string& key, const std::string& plainText) {
  Encrypter encrypter(key);

  std::string cipherText = encrypter.encrypt(plainText);
  std::string decryptedText = encrypter.decrypt(cipherText);

  std::cout << "Key: " << key << std::endl;
  std::cout << "Plain Text: " << plainText << std::endl;
  std::cout << "Cipher Text: " << cipherText << std::endl;
  std::cout << "Decrypted Text: " << decryptedText << std::endl;

  // Check that the decrypted text matches the original plaintext
  assert(decryptedText == plainText);
}

void enc_tester()
{
  testEncrypter("your-secret-key", "Hello, World!");
  testEncrypter("short-key", "Short key test");
  testEncrypter("this-is-a-very-long-key-that-is-more-than-32-bytes", "Long key test");
  testEncrypter("sixteen-byte-key", "16 byte key test");
  testEncrypter("twentyfour-byte-key-for-test", "24 byte key test");
  testEncrypter("thirtytwo-byte-key-for-encryption-test", "32 byte key test");
  std::cout << "All encrypter tests passed!" << std::endl;
}
void testPasswordKeeper()
{
  // Create an instance of Encrypter
  Encrypter encrypter ("your-secret-key");

  // Create an instance of Password_keeper
  Password_keeper passwordKeeper (encrypter);

  // Test storeUser method
  passwordKeeper.storeUser ("testUser", "testPassword");

  // Test authenticateUser method
  bool isAuthenticated = passwordKeeper.authenticateUser ("testUser", "testPassword");
  std::cout << "Authentication result: "
            << (isAuthenticated ? "Success" : "Failure") << std::endl;

  // Test storePassword method
  passwordKeeper.storePassword ("testUser", "testSite", "testSitePassword");

  // Test retrievePassword method
  std::string retrievedPassword = passwordKeeper.retrievePassword ("testUser", "testSite");
  std::cout << "Retrieved password: " << retrievedPassword << std::endl;

  std::cout << "All keeper tests passed!" << std::endl;
}

int main() {
//        enc_tester();
//    testPasswordKeeper();
    int choice;
    std::string username, password;
  while (true)
  {
    try
    {
      std::cout << "1. Register\n";
      std::cout << "2. Login\n";
      std::cout << "3. Quit\n";
      std::cout << "Enter your choice: ";
      std::cin >> choice;

      if (choice == 1)
      {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        Encrypter encrypter (password);
        Password_keeper passwordKeeper (encrypter);
        passwordKeeper.storeUser (username, password);
        std::cout << "User registered successfully!\n";
      }
      else if (choice == 2)
      {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        Encrypter encrypter (password);
        Password_keeper passwordKeeper (encrypter);
        if (passwordKeeper.authenticateUser (username, password))
        {
          std::cout << "Login successful!\n";
          int passwordChoice;
          std::string passwordName, newPassword;

          while (true)
          {
            std::cout << "1. Add new password\n";
            std::cout << "2. Delete password\n";
            std::cout << "3. Get password\n";
            std::cout << "4. Logout\n";
            std::cout << "Enter your choice: ";
            std::cin >> passwordChoice;

            if (passwordChoice == 1)
            {
              std::cout << "Enter password name: ";
              std::cin >> passwordName;
              std::cout << "Enter new password: ";
              std::cin >> newPassword;
              passwordKeeper.storePassword (username, passwordName, newPassword);
              std::cout << "Password added successfully!\n";
            }
            else if (passwordChoice == 2)
            {
              std::cout << "Enter password name: ";
              std::cin >> passwordName;
              passwordKeeper.deletePassword (username, passwordName);
              std::cout << "Password deleted successfully!\n";
            }
            else if (passwordChoice == 3)
            {
              std::cout << "Enter password name: ";
              std::cin >> passwordName;
              std::string retrievedPassword = passwordKeeper.retrievePassword (username, passwordName);
              std::cout << "Password: " << retrievedPassword << "\n";
            }
            else if (passwordChoice == 4)
            {
              break;
            }
            else
            {
              std::cout << "Invalid choice. Please enter 1, 2, 3, or 4.\n";
            }
          }
        }
        else
        {
          std::cout << "Invalid username or password!\n";
        }
      }
      else if (choice == 3)
      {
        return 0;
      }
      else
      {
        std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  }
    return 0;
  }