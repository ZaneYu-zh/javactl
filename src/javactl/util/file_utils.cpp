#include "javactl/util/file_utils.hpp"

#include <filesystem>
#include <fstream>

namespace javactl::util {
    bool FileUtils::exists(const std::string &path) {
        return std::filesystem::exists(path);
    }

    std::string FileUtils::readFile(const std::string &filePath) {
        std::ifstream file(filePath);
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }

    void FileUtils::writeFile(const std::string &filePath, const std::string &content) {
        std::ofstream file(filePath);
        file << content;
    }
}