#ifndef MIRROR_RESOLVER_H
#define MIRROR_RESOLVER_H

#include <string>

namespace javactl::download {
    class MirrorResolver {
    public:
        static std::string execute(const std::string &url = "https://jdk.java.net/archive/");
    };
}

#endif
