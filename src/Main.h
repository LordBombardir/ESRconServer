#pragma once

#include <endstone/plugin/plugin.h>

namespace rcon_server {

class Main : public endstone::Plugin {
public:
    void onLoad() override;
    void onEnable() override;
    void onDisable() override;

    static Main* getInstance();

private:
    static Main* instance;
};

} // namespace rcon_server