//
// Created by alexandre on 04/10/23.
//

#include "IsParallax.hpp"

namespace Client {

    size_t IsParallax::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsParallax");
    }

}
