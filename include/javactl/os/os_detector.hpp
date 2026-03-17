#ifndef OS_DETECTOR_H
#define OS_DETECTOR_H

#include <string>

namespace javactl::os {
    class OsDetector {
    public:
        static std::string getOsType();

        static std::string getArchType();

        static std::string getUserHomeDir();

        static std::string getTempDir();

        static std::string getDefaultJavaInstallRoot();

        static std::string getDefaultConfigDir();
    };
}

#endif