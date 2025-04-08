#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <algorithm>
#include <cctype>

#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"
#include "./src/app/fileHandling/ReadEnv.hpp"

namespace fs = std::filesystem;

inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v") {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v") {
    return ltrim(rtrim(s, t), t);
}

int main(int argc, char* argv[]) {
    std::string directory;
    std::string action;

    std::cout << "Enter the directory path: ";
    std::getline(std::cin, directory);
    trim(directory);

    std::cout << "Enter the action (encrypt/decrypt): ";
    std::getline(std::cin, action);
    trim(action);

    if (action != "encrypt" && action != "decrypt") {
        std::cerr << "Invalid action. Please enter 'encrypt' or 'decrypt'." << std::endl;
        return 1;
    }

    int encryptionKey;
    try {
        ReadEnv envReader;
        std::string keyStr = envReader.getenv();
        if (keyStr.empty()) {
            throw std::runtime_error("Encryption key not found or empty in .env file.");
        }

        try {
            encryptionKey = std::stoi(keyStr);
        } catch (const std::invalid_argument& ia) {
            throw std::runtime_error("Invalid key format in .env file (not a number): " + keyStr);
        } catch (const std::out_of_range& oor) {
            throw std::runtime_error("Key in .env file is out of integer range: " + keyStr);
        }

        std::cout << "Using encryption key: " << encryptionKey << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error initializing: " << e.what() << std::endl;
        return 1;
    }

    try {
        if (fs::exists(directory) && fs::is_directory(directory)) {
            ProcessManagement processManagement;

            std::cout << "Scanning directory: " << directory << std::endl;
            for (const auto& entry : fs::recursive_directory_iterator(directory, fs::directory_options::skip_permission_denied)) {
                try {
                    if (entry.is_regular_file()) {
                        std::string filePath = entry.path().string();
                        Action taskAction = (action == "encrypt") ? Action::ENCRYPT : Action::DECRYPT;
                        auto task = std::make_unique<Task>(taskAction, filePath);
                        if (!processManagement.submitToQueue(std::move(task))) {
                            std::cerr << "Warning: Failed to submit task for: " << filePath << std::endl;
                        }
                    }
                } catch (const fs::filesystem_error& fileEx) {
                    std::cerr << "Error accessing file system entry " << entry.path().string() << ": " << fileEx.what() << std::endl;
                } catch (const std::exception& stdEx) {
                    std::cerr << "Error processing directory entry " << entry.path().string() << ": " << stdEx.what() << std::endl;
                }
            }

            processManagement.executeTasks(encryptionKey);

        } else {
            std::cerr << "Error: Problem with path [" << directory << "]" << std::endl;
            if (!fs::exists(directory)) {
                std::cerr << "Reason: Path does not exist." << std::endl;
            } else {
                std::cerr << "Reason: Path exists but is not a directory." << std::endl;
            }
            return 1;
        }
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Filesystem error during processing: " << ex.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Operation completed." << std::endl;
    return 0;
}
