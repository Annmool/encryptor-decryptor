#include "IO.hpp"
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>

IO::IO(const std::string& file_path) : path_name(file_path) {
    file_stream.open(file_path, std::ios::in | std::ios::out | std::ios::binary);
    if (!file_stream.is_open()) {
        throw std::runtime_error("IO Error: Unable to open file: " + file_path);
    }
}

std::fstream IO::getFileStream() {
    return std::move(file_stream);
}

IO::~IO() {
    if (file_stream.is_open()) {
        file_stream.close();
    }
}
