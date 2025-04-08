#ifndef READENV_HPP
#define READENV_HPP

#include <string>

class ReadEnv {
public:
    // Reads the key from the .env file.
    // Returns the key as a string, or an empty string on failure.
    // Trims whitespace from the key.
    std::string getenv();
};

#endif // READENV_HPP
