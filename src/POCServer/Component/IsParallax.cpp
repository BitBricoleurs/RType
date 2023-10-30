//
// Created by alexandre on 04/10/23.
//

#include "IsParallax.hpp"

namespace Server {

    size_t IsParallax::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsParallax");
    }

    IsParallax::IsParallax(float layer, bool isLooping, ParallaxType type) : layer(layer), isLooping(isLooping), type(type)
    {
        
    }

} // namespace Server

