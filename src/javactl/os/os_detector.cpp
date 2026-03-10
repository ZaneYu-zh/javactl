#include "javactl/os/os_detector.hpp"

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
            return "unknown";
#endif
        }

        std::string getArchType()
        {
#ifdef _WIN32
            SYSTEM_INFO si;
            GetNativeSystemInfo(&si);
            switch (si.wProcessorArchitecture)
            {
                case PROCESSOR_ARCHITECTURE_AMD64:
                    return "x64";
                case PROCESSOR_ARCHITECTURE_ARM64:
                    return "arm64";
                default:
                    return "unknown";
            }
        }
#elif __APPLE__ || __linux__
        struct ustname un;
        if (ustname(&un) != 0)
        {
            return "unknown";
        }
        std::string machine(un.machine);
        if (machine == "x86_64" || machine == "amd64")
        {
            return "x64";
        }
        else if (machine == "aarch64" || machine == "arm64")
        {
            return "arm64";
        }
        else
        {
            return "unknown";
        }
#else
        return "unknown";
#endif
    }
}