#include "Main.h"
#include "manager/MainManager.h"

namespace rcon_server {

Main* Main::instance = nullptr;

void Main::onLoad() {
    instance = this;

    getLogger().info("The mod is loading...");

    if (!manager::MainManager::initManagers(*this)) {
        throw std::runtime_error("Failed to initialize managers!");
    }

    getLogger().info("The mod has been successfully loaded!");
}

void Main::onEnable() {
    getLogger().info("The mod is enabling...");

    manager::MainManager::startRconServer();

    getLogger().info("The mod has been successfully enabled!");
    getLogger().info("Author: vk.com/lordbomba");
}

void Main::onDisable() {
    getLogger().info("The mod is disabling...");

    manager::MainManager::stopRconServer();

    getLogger().info("The mod has been successfully disabled!");
}

Main* Main::getInstance() { return instance; }

} // namespace rcon_server

ENDSTONE_PLUGIN("rcon_server", "1.0.0", rcon_server::Main) { description = "Implementation RCON for Endstone"; }