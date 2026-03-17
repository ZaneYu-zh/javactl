#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "javactl_config.hpp"
#include "mirror_config.hpp"
#include <vector>

namespace javactl::config {
    class ConfigManager {
    public:
        static ConfigManager& get_instance();

        void init();

        std::string getJavaInstallRoot();

        std::string getRemoteDirectory();

        std::string getDefaultMirrorName();

        bool isChecksumVerifyEnabled() const;

        int getDownloadTimeout() const;

        int getRetryCount() const;

    private:
        void loadConfig();

        void generateDefaultConfig();

        void saveConfig();

    private:
        bool m_inited{false};
        JavactlConfig m_config;
        std::vector<MirrorConfig> m_mirrors;
        std::string m_configPath;
    };
}

# endif