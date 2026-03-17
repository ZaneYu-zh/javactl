#include "javactl/config/config_manager.hpp"

#include <iostream>
#include "javactl/os/os_detector.hpp"
#include "javactl/util/file_utils.hpp"
#include "javactl/config/mirror_config.hpp"
#include <nlohmann/json.hpp>

namespace javactl::config {
    ConfigManager &ConfigManager::get_instance() {
        static ConfigManager instance;
        return instance;
    }

    ConfigManager::ConfigManager() : m_config() {
        const std::string configDir = os::OsDetector::getDefaultConfigDir();
        m_configPath = configDir + "/config.json";
    }

    void ConfigManager::init() {
        if (m_inited) return;

        if (!util::FileUtils::exists(m_configPath)) {
            generateDefaultConfig();
        }

        loadConfig();
        m_inited = true;
    }

    std::string ConfigManager::getMirrorUrl() const {
        if (!m_inited) return "";

        for (const auto &mirror: m_mirrors) {
            if (mirror.name == m_config.defaultMirror) {
                return mirror.url;
            }
        }

        return "";
    }

    std::string ConfigManager::getJavaInstallRoot() const {
        if (!m_inited) return "";

        if (m_config.javaInstallRoot.empty()) {
            return os::OsDetector::getDefaultJavaInstallRoot();
        }

        return m_config.javaInstallRoot;
    }

    std::string ConfigManager::getDefaultMirrorName() const {
        if (!m_inited) return "";

        return m_config.defaultMirror;
    }

    bool ConfigManager::isChecksumVerifyEnabled() const {
        return m_config.enableChecksumVerify;
    }

    int ConfigManager::getDownloadTimeout() const {
        return m_config.downloadTimeout;
    }

    int ConfigManager::getRetryCount() const {
        return m_config.retryCount;
    }

    void ConfigManager::loadConfig() {
        try {
            std::string content = util::FileUtils::readFile(m_configPath);
            nlohmann::json j = nlohmann::json::parse(content);

            const auto &global = j["global"];
            m_config.defaultMirror = global["default_mirror"];
            m_config.javaInstallRoot = global["java_install_root"];
            m_config.enableChecksumVerify = global["enable_checksum_verify"];
            m_config.downloadTimeout = global["download_timeout"];
            m_config.retryCount = global["retry_count"];

            m_mirrors.clear();
            for (const auto &item: j["mirrors"]) {
                MirrorConfig mirror;
                mirror.name = item["name"];
                mirror.description = item["description"];
                mirror.url = item["url"];
                m_mirrors.push_back(mirror);
            }
        } catch (...) {
        }
    }

    void ConfigManager::generateDefaultConfig() const {
        nlohmann::json j;

        j["global"]["default_mirror"] = "jdk.java.net";
        j["global"]["java_install_root"] = "";
        j["global"]["enable_checksum_verify"] = true;
        j["global"]["download_timeout"] = 300;
        j["global"]["retry_count"] = 3;

        j["mirrors"] = nlohmann::json::array();
        j["mirrors"][0]["name"] = "jdk.java.net";
        j["mirrors"][0]["description"] = "Archived OpenJDK GA Releases";
        j["mirrors"][0]["url"] = "https://jdk.java.net/archive/";

        util::FileUtils::writeFile(m_configPath, j.dump(2));
        std::cout << "Default config generated: " << m_configPath << std::endl;
    }

    void ConfigManager::saveConfig() {
        if (!m_inited) return;

        try {
            nlohmann::json j;

            j["global"]["default_mirror"] = m_config.defaultMirror;
            j["global"]["java_install_root"] = m_config.javaInstallRoot;
            j["global"]["enable_checksum_verify"] = m_config.enableChecksumVerify;
            j["global"]["download_timeout"] = m_config.downloadTimeout;
            j["global"]["retry_count"] = m_config.retryCount;

            j["mirrors"] = nlohmann::json::array();
            for (size_t i = 0; i < m_mirrors.size(); ++i) {
                const auto &[name, description, url] = m_mirrors[i];
                j["mirrors"][i]["name"] = name;
                j["mirrors"][i]["description"] = description;
                j["mirrors"][i]["url"] = url;
            }

            util::FileUtils::writeFile(m_configPath, j.dump(2));
        } catch (...) {
        }
    }
}