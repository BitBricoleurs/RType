//
// Created by alexandre on 03/10/23.
//

#include "IsPowerUp.hpp"

namespace Server {

    size_t IsPowerUp::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsPowerUp");
    }
}
