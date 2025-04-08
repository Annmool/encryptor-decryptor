#include "ReadEnv.hpp"
#include "IO.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

inline std::string& ltrim_env(std::string& s, const char* t = " \t\n\r\f\v") {
    s.erase(0, s.find_first_not_of(t));
    return s;
}
inline std::string& rtrim_env(std::string& s, const char* t = " \t\n\r\f\v") {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}
inline std::string& trim_env(std::string& s, const char* t = " \t\n\r\f\v") {
    return ltrim_env(rtrim_env(s, t), t);
}

std::string ReadEnv::getenv() {
    std::string env_path = ".env";
    try {
        IO io(env_path);
        std::fstream f_stream = io.getFileStream();

        if (!f_stream.is_open()) {
            std::cerr << "Error: ReadEnv could not obtain open stream for .env file: " << env_path << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << f_stream.rdbuf();

        std::string content = buffer.str();
        trim_env(content);

        return content;

    } catch (const std::runtime_error& e) {
        return "";
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error reading environment file (" << env_path << "): " << e.what() << std::endl;
        return "";
    }
}
