#ifndef MIRROR_CONFIG_H
#define MIRROR_CONFIG_H

#include <string>

namespace javactl::config {
    struct  MirrorConfig {
        std::string name;
        std::string description;
        std::string directoryUrl;
    };
}

#endif
