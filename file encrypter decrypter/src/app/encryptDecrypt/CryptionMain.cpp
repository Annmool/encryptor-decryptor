#include <iostream>
#include "Cryption.hpp" 
#include <string>     

int main(int argc, char* argv[]) {
   
    if (argc != 3) { 
        std::cerr << "Usage: ./cryption <task_data_string> <key>" << std::endl;
        std::cerr << "Example: ./cryption \"/path/to/file.txt,ENCRYPT\" 12345" << std::endl;
        return 1;
    }

    std::string taskData = argv[1];
    int key;

    try {
        key = std::stoi(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Error: Invalid key provided: " << argv[2] << " - " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Executing cryption with Task Data: [" << taskData << "] and Key: [" << key << "]" << std::endl;

    int result = executeCryption(taskData, key);

    if (result == 0) {
        std::cout << "Cryption executed successfully." << std::endl;
    } else {
        std::cerr << "Cryption execution failed." << std::endl;
    }

    return result; 
}
