#ifndef TASK_HPP
#define TASK_HPP

#include "../fileHandling/IO.hpp" // Needed for openFileStream
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept> // For std::runtime_error
#include <utility>   // For std::move

enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task {
    // --- Members (Order matters for initializer list warning) ---
    std::string filePath; // Declared first
    Action action;        // Declared second

    // --- Constructor (Initializes members in declaration order) ---
    Task(Action act, std::string path)
        : filePath(std::move(path)), action(act) // Initialize filePath first, then action
         {}

    // --- Member Functions ---

    // Serialize task data (path and action) to string
    std::string toString() const {
        std::ostringstream oss;
        oss << filePath << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return oss.str();
    }

    // Deserialize task data from string
    static Task fromString(const std::string& taskData) {
        std::istringstream iss(taskData);
        std::string parsedFilePath;
        std::string actionStr;

        // Parse the string: "filepath,ACTION"
        if (std::getline(iss, parsedFilePath, ',') && std::getline(iss, actionStr)) {
            Action parsedAction;
            if (actionStr == "ENCRYPT") {
                parsedAction = Action::ENCRYPT;
            } else if (actionStr == "DECRYPT") {
                parsedAction = Action::DECRYPT;
            } else {
                 throw std::runtime_error("Invalid action string in task data: " + actionStr);
            }
            // Return a new Task object with the parsed data
            return Task(parsedAction, parsedFilePath);
        } else {
            throw std::runtime_error("Invalid task data format: " + taskData);
        }
    }

    // Method to open the file stream when needed
    std::fstream openFileStream() const {
        // Use IO class to handle opening in binary read/write mode
        IO io(filePath);
        // Get the stream directly - allows NRVO (avoids -Wpessimizing-move warning)
        std::fstream stream = io.getFileStream();

        // Check if the file was successfully opened by IO (IO constructor should throw, but double check)
        if (!stream.is_open()) {
            // Throw an exception if opening failed
            throw std::runtime_error("Failed to open file stream for: " + filePath);
        }
        // Return the opened stream
        return stream; // RVO or move semantics will handle the return
    }
};

#endif // TASK_HPP
