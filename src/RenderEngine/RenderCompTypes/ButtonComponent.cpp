//
// Created by Theophilus Homawoo on 13/10/2023.
//

#include "ButtonComponent.hpp"

namespace RenderEngine {
    size_t ButtonComponent::getComponentType(){
        return GameEngine::ComponentsType::getNewComponentType("ButtonComponent");
    }
} // GameEngine