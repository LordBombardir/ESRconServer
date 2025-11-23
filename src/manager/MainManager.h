#pragma once

#include "../rcon/Server.h"
#include <endstone/plugin/plugin.h>

namespace rcon_server::manager {

class MainManager final {
public:
    static bool initManagers(const endstone::Plugin& plugin);

    static void startRconServer();
    static void stopRconServer();

private:
    static std::shared_ptr<rcon::Server> rconServer;

    static void        onNewConnection(const std::shared_ptr<rcon::ConnectedClient> client);
    static void        onClientAuth(const std::shared_ptr<rcon::ConnectedClient> client);
    static void        onClientDisconnect(const std::shared_ptr<rcon::ConnectedClient> client);
    static std::string onCommand(const std::shared_ptr<rcon::ConnectedClient> client, std::string_view command);
    static void        onDebugInfo(const std::shared_ptr<rcon::ConnectedClient> client, const std::string& debugInfo);
};

} // namespace rcon_server::manager