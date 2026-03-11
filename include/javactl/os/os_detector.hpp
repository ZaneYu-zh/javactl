#ifndef OS_DETECTOR_H
#define OS_DETECTOR_H

#include <string>

namespace javactl::os {
    std::string getOsType();

    std::string getArchType();

    std::string getUserHomeDir();

    std::string getTempDir();

    std::string getDefaultJavaInstallRoot();
}

#endif
