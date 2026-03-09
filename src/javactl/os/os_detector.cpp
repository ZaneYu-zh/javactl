#include "javactl/os/os_detector.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__ || __linux__
#include <sys/utsname.h>
#endif

namespace javactl
{
    namespace os
    {
        std::string getOsType()
        {
#ifdef _WIN32
            return "win";
#elif __APPLE__
            return "mac";
#elif __linux__
            return "linux";
#else
            std::cerr << 1111111111 << std::endl;
#endif
        }

//         std::string getArchType()
//         {
// #ifdef _WIN32
//             SYSTEM_INFO si;
//             GetNa

//         }

    }
}