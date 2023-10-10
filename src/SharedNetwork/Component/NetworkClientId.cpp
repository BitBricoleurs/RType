//
// Created by Clément Lagasse on 05/10/2023.
//

#include "NetworkClientId.hpp"

NetworkClientId::NetworkClientId(unsigned int id) : id(id) {}

size_t NetworkClientId::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("NetworkClientId");
}
