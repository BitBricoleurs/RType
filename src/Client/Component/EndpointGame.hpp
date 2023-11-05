//
// Created by Clément Lagasse on 27/10/2023.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "RenderEngine.hpp"

namespace Client {

    class EndpointGame : public GameEngine::AComponent {
    public:
      EndpointGame(std::string &host, std::string &port):
        _host(host), _port(port) {};

      size_t getComponentType() override;

      std::string _host;
      std::string _port;
    };
}
