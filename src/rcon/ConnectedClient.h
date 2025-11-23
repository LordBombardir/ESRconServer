#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <memory>

namespace rcon_server::rcon {

struct ConnectedClient {
    std::shared_ptr<boost::asio::ip::tcp::socket> socket;
    bool                                          isAuthenticated;
};

} // namespace rcon_server::rcon