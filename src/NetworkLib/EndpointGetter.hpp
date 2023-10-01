//
// Created by Clément Lagasse on 01/10/2023.
//

#pragma once

#include <vector>
#include <asio.hpp>

namespace Network {
    class Interface;
    class EndpointGetter {
    public:
      static unsigned int getIdByEndpoint(const asio::ip::udp::endpoint& endpoint, const std::vector<std::shared_ptr<Network::Interface> >* _clients);

      static asio::ip::udp::endpoint getEndpointById(unsigned int id, const std::vector<std::shared_ptr<Network::Interface> >* _clients);
    };
}
