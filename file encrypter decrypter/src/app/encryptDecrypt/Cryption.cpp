#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>

int executeCryption(const std::string& taskData, int key) {
    std::string filePathForError = "Unknown path";
    try {
        Task task = Task::fromString(taskData);
        filePathForError = task.filePath;

        std::fstream f_stream = task.openFileStream();

        if (task.action == Action::ENCRYPT) {
            char ch;
            while (f_stream.get(ch)) {
                unsigned char originalChar = static_cast<unsigned char>(ch);
                unsigned char encryptedChar = (originalChar + key);

                f_stream.seekp(-1, std::ios::cur);
                f_stream.put(static_cast<char>(encryptedChar));
                f_stream.seekp(0, std::ios::cur);
            }
        } else { // DECRYPT
            char ch;
            while (f_stream.get(ch)) {
                unsigned char encryptedChar = static_cast<unsigned char>(ch);
                unsigned char decryptedChar = (encryptedChar - key);

                f_stream.seekp(-1, std::ios::cur);
                f_stream.put(static_cast<char>(decryptedChar));
                f_stream.seekp(0, std::ios::cur);
            }
        }

        if (f_stream.bad()) {
             std::cerr << "Error: Stream error after processing file: " << filePathForError << std::endl;
             return 2;
        } else if (!f_stream.eof()) {
             std::cerr << "Warning: Processing stopped before EOF for file: " << filePathForError << std::endl;
        }

        return 0;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error processing file '" << filePathForError << "' (Task Data: '" << taskData << "'): " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error processing file '" << filePathForError << "' (Task Data: '" << taskData << "'): " << e.what() << std::endl;
        return 1;
    }
}
