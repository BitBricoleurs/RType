//
// Created by alexandre on 03/10/23.
//

#include "IsPowerUp.hpp"

namespace Client {

    size_t IsPowerUp::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsPowerUp");
    }

}
