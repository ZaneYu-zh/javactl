#include "javactl/os/os_detector.hpp"

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__ || __linux__
#include <sys/utsname.h>
#endif

namespace javactl::os {
    std::string OsDetector::getOsType() {
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

    std::string OsDetector::getArchType() {
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

    std::string OsDetector::getUserHomeDir() {
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
            return "unknown";
        }
        return {homeEnv};
    }

    std::string OsDetector::getTempDir() {
        const char *tempEnv = nullptr;
#ifdef _WIN32
        tempEnv = std::getenv("TEMP");
        if (!tempEnv) {
            tempEnv = std::getenv("TMP");
        }
#else
        tempEnv = std::getenv("TMPDIR");
        if (!tempEnv) {
            return "/tmp";
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

    std::string OsDetector::getDefaultJavaInstallRoot() {
        const std::string homeDir = getUserHomeDir();
        return homeDir + "/.javactl";
    }

    std::string OsDetector::getDefaultConfigDir() {
        const std::string home = getUserHomeDir();
        std::string configDir;

#ifdef _WIN32
        configDir = home + R"(\AppData\Roaming\javactl)";
#else
        configDir = home + "/javactl";
#endif

        std::filesystem::create_directories(configDir);
        return configDir;
    }

    std::string OsDetector::getEnvVar(const char *name) {
        char* buffer = nullptr;
        size_t len = 0;

#ifdef _WIN32
        if (_dupenv_s(&buffer, &len, name) != 0 || buffer == nullptr) {
            return "";
        }
#else
        buffer = std::getenv(name);
        if (buffer == nullptr) {
            return "";
        }
        len = std::strlen(buffer);
        if (len == 0) {
            return "";
        }
#endif
        std::string result(buffer);
#ifdef _WIN32
        std::free(buffer);
#endif
        return result;
    }

    std::string OsDetector::getEnvVar(const char *name, const char *fallback) {
        std::string result = getEnvVar(name);
        return result.empty() ? fallback : result;
    }
}
