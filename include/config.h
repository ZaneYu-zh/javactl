#pragma once    
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct Mirror
{
    std::string name;
    std::string url;
    int priority;
};

struct Config
{
    std::vector<Mirror> mirrors;
    std::string default_version;
    std::string install_path;

    static Config load();
    void save() const;
};
