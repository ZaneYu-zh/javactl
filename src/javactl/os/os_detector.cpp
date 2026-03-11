#include "javactl/os/os_detector.hpp"

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__ || __linux__
#include <sys/utsname.h>
#endif

namespace javactl::os {
    std::string getOsType() {
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

    std::string getArchType() {
#ifdef _WIN32
        SYSTEM_INFO si;
        GetNativeSystemInfo(&si);
        switch (si.wProcessorArchitecture) {
            case PROCESSOR_ARCHITECTURE_AMD64:
                return "x64";
            case PROCESSOR_ARCHITECTURE_ARM64:
                return "arm64";
            default:
                return "unknown";
        }
#elif __APPLE__ || __linux__
        struct utsname un;
        if (uname(&un) != 0) {
            return "unknown";
        }
        std::string machine(un.machine);
        if (machine == "x86_64" || machine == "amd64") {
            return "x64";
        } else if (machine == "aarch64" || machine == "arm64") {
            return "arm64";
        } else {
            return "unknown";
        }
#else
        return "unknown";
#endif
    }

    std::string getUserHomeDir() {
        const char *homeEnv = nullptr;
#ifdef _WIN32
        homeEnv = std::getenv("USERPROFILE");
        if (!homeEnv) {
            homeEnv = std::getenv("HOME");
        }
#else
        homeEnv = std::getenv("HOME");
#endif
        if (!homeEnv || strlen(homeEnv) == 0) {
            return "uknown";
        }
        return {homeEnv};
    }

    std::string getTempDir() {
        const char *tempEnv = nullptr;
#ifdef _WIN32
        tempEnv = std::getenv("TEMP");
        if (!tempEnv) {
            tempEnv = std::getenv("TMP");
        }
#else
        tempEnv = std::getenv("TMPDIR");
        if (!tempEnv) {
            return "/tmp"
        }
#endif

        if (!tempEnv || strlen(tempEnv) == 0) {
#ifdef _WIN32
            return "unknown";
#else
            return "/tmp";
#endif
        }

        return {tempEnv};
    }

    std::string getDefaultJavaInstallRoot() {
        const std::string homeDir = getUserHomeDir();
        return homeDir + "/.javactl";
    }
}
