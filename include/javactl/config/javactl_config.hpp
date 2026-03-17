#ifndef JAVACTL_CONFIG_H
#define JAVACTL_CONFIG_H
#include <string>

namespace javactl::config {
    struct JavactlConfig {
        std::string defaultMirror;
        std::string javaInstallRoot;
        bool enableChecksumVerify;
        int downloadTimeout;
        int retryCount;
    };
}

#endif
