#include "ConfigManager.h"
#include <fstream>

namespace rcon_server::manager {

Config ConfigManager::config;

bool ConfigManager::init(const endstone::Plugin& plugin) {
    auto path = plugin.getDataFolder() / "config.json";

    try {
        return load(path);
    } catch (const std::exception& e) {
        plugin.getLogger().warning("[ConfigManager] Failed to load configuration: {}.", e.what());
        plugin.getLogger().warning("[ConfigManager] Trying to create a new one...");
    }

    try {
        return save(path);
    } catch (const std::exception& e) {
        plugin.getLogger().error("[ConfigManager] Failed to load configuration: {}.", e.what());
        return false;
    }
}

bool ConfigManager::load(const std::filesystem::path& filePath) {
    if (!std::filesystem::exists(filePath)) {
        throw std::runtime_error("File not found!");
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    nlohmann::json j;
    file >> j;

    config = j.get<Config>();
    return true;
}

bool ConfigManager::save(const std::filesystem::path& filePath) {
    if (filePath.has_parent_path()) {
        std::filesystem::create_directories(filePath.parent_path());
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    try {
        nlohmann::json j = config;
        file << j.dump(4);
    } catch (...) {
        return false;
    }

    return true;
}

const Config& ConfigManager::getConfig() { return config; }

} // namespace rcon_server::manager