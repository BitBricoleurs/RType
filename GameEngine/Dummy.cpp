//
// Created by Theophilus Homawoo on 24/09/2023.
//

#include <iostream>
#include "ComponentsType.hpp"

namespace GameEngine {
    size_t spriteComponentType = ComponentsType::getNewComponentType("SpriteComponent");
    size_t textComponentType = ComponentsType::getNewComponentType("TextComponent");
    size_t parallaxComponentType = ComponentsType::getNewComponentType("ParallaxComponent");
    size_t animationComponentType = ComponentsType::getNewComponentType("AudioComponent");
}
