#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "javactl/config/javactl_config.hpp"
#include <vector>

namespace javactl::config {
    class MirrorConfig;

    class ConfigManager {
    public:
        static ConfigManager &get_instance();

        void init();

        [[nodiscard]] std::string getJavaInstallRoot() const;

        [[nodiscard]] std::string getMirrorUrl() const;

        [[nodiscard]] std::string getDefaultMirrorName() const;

        [[nodiscard]] bool isChecksumVerifyEnabled() const;

        [[nodiscard]] int getDownloadTimeout() const;

        [[nodiscard]] int getRetryCount() const;

    private:
        ConfigManager();

        void loadConfig();

        void generateDefaultConfig() const;

        void saveConfig();

    private:
        bool m_inited{false};

        JavactlConfig m_config;

        std::vector<MirrorConfig> m_mirrors;

        std::string m_configPath;
    };
}

# endif