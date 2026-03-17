#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

namespace javactl::util {
    class FileUtils {
    public:
        static bool exists(const std::string &path);

        static std::string readFile(const std::string &filePath);

        static void writeFile(const std::string &filePath, const std::string &content);
    };
}

#endif