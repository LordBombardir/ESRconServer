#pragma once

#include "Config.h"
#include <filesystem>
#include <endstone/plugin/plugin.h>

namespace rcon_server::manager {

class ConfigManager {
public:
    static bool init(const endstone::Plugin& plugin);

    static const Config& getConfig();

private:
    static Config config;
    
    static bool load(const std::filesystem::path& filePath);
    static bool save(const std::filesystem::path& filePath);
};

} // namespace rcon_server::manager