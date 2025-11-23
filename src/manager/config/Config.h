#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace rcon_server::manager {

struct Config {
    unsigned short port           = 19130;
    unsigned short maxConnections = 5;
    std::string    password       = "Change this to your password";

    bool logOnNewConnection    = true;
    bool logOnClientAuth       = true;
    bool logOnClientDisconnect = true;
    bool logOnCommand          = true;
    bool logOnDebugInfo        = false;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        Config,
        port,
        maxConnections,
        password,
        logOnNewConnection,
        logOnClientAuth,
        logOnClientDisconnect,
        logOnCommand,
        logOnDebugInfo
    )
};

} // namespace rcon_server::manager