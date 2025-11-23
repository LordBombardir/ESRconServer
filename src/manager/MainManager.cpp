#include "MainManager.h"
#include "../Main.h"
#include "config/ConfigManager.h"
#include <endstone/command/command_sender_wrapper.h>
#include <endstone/command/console_command_sender.h>
#include <endstone/server.h>

namespace rcon_server::manager {

std::shared_ptr<rcon::Server> MainManager::rconServer = nullptr;

bool MainManager::initManagers(const endstone::Plugin& plugin) {
    try {
        return ConfigManager::init(plugin);
    } catch (const std::exception& error) {
        plugin.getLogger().error("Failed to initialize ConfigManager: {}", error.what());
        return false;
    }
}

void MainManager::startRconServer() {
    if (rconServer != nullptr) {
        throw std::runtime_error("The RCON server is already started!");
    }

    rconServer = std::make_shared<rcon::Server>(
        ConfigManager::getConfig().port,
        ConfigManager::getConfig().maxConnections,
        ConfigManager::getConfig().password,
        ConfigManager::getConfig().logOnNewConnection ? &onNewConnection : nullptr,
        ConfigManager::getConfig().logOnClientAuth ? &onClientAuth : nullptr,
        ConfigManager::getConfig().logOnClientDisconnect ? &onClientDisconnect : nullptr,
        &onCommand,
        ConfigManager::getConfig().logOnDebugInfo ? &onDebugInfo : nullptr
    );

    rconServer->start();
}

void MainManager::stopRconServer() {
    if (rconServer == nullptr) {
        throw std::runtime_error("The RCON server is not running!");
    }

    rconServer->stop();
}

void MainManager::onNewConnection(const std::shared_ptr<rcon::ConnectedClient> client) {
    Main::getInstance()->getLogger().info(
        "New connection from {}:{}",
        client->socket->remote_endpoint().address().to_string(),
        client->socket->remote_endpoint().port()
    );
}

void MainManager::onClientAuth(const std::shared_ptr<rcon::ConnectedClient> client) {
    Main::getInstance()->getLogger().info(
        "Client {}:{} has successfully authorized",
        client->socket->remote_endpoint().address().to_string(),
        client->socket->remote_endpoint().port()
    );
}

void MainManager::onClientDisconnect(const std::shared_ptr<rcon::ConnectedClient> client) {
    Main::getInstance()->getLogger().info(
        "Client {}:{} disconnected",
        client->socket->remote_endpoint().address().to_string(),
        client->socket->remote_endpoint().port()
    );
}

std::string MainManager::onCommand(const std::shared_ptr<rcon::ConnectedClient> client, std::string_view command) {
    if (ConfigManager::getConfig().logOnCommand) {
        Main::getInstance()->getLogger().info(
            "Client {}:{} has sent a new command: {}",
            client->socket->remote_endpoint().address().to_string(),
            client->socket->remote_endpoint().port(),
            command
        );
    }

    auto& server = Main::getInstance()->getServer();
    auto& sender = server.getCommandSender();

    std::string outputStr = "";

    endstone::CommandSenderWrapper::Callback callback = [&server, &outputStr](const endstone::Message& msg) -> void {
        if (std::holds_alternative<std::string>(msg)) {
            outputStr += std::get<std::string>(msg);
        } else if (std::holds_alternative<endstone::Translatable>(msg)) {
            const auto& translatable = std::get<endstone::Translatable>(msg);
            outputStr += server.getLanguage().translate(translatable.getText(), translatable.getParameters());
        }
    };
    auto wrapper = endstone::CommandSenderWrapper(sender, callback, callback);

    server.dispatchCommand(wrapper, std::string{command});
    return outputStr;
}

void MainManager::onDebugInfo(const std::shared_ptr<rcon::ConnectedClient> client, const std::string& debugInfo) {
    Main::getInstance()->getLogger().info(
        "[Client {}:{}] {}",
        client->socket->remote_endpoint().address().to_string(),
        client->socket->remote_endpoint().port(),
        debugInfo
    );
}

} // namespace rcon_server::manager