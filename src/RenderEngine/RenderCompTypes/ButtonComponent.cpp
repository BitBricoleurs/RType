//
// Created by Theophilus Homawoo on 13/10/2023.
//

#include "ButtonComponent.hpp"

namespace GameEngine {
    size_t ButtonComponent::getComponentType(){
        return ComponentsType::getNewComponentType("ButtonComponent");
    }
} // GameEngine