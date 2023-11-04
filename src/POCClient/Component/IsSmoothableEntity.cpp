//
// Created by clagasse on 10/31/23.
//

#include "IsSmoothableEntity.hpp"

namespace Client {

     size_t IsSmoothableEntity::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsSmoothableEntity");
     }

}