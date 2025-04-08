#ifndef IO_HPP
#define IO_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>

class IO {
public:
    IO(const std::string& file_path);
    ~IO();
    std::fstream getFileStream();
    IO(const IO&) = delete;
    IO& operator=(const IO&) = delete;
    IO(IO&&) = default;
    IO& operator=(IO&&) = default;

private:
    std::fstream file_stream;
    std::string path_name;
};

#endif // IO_HPP
