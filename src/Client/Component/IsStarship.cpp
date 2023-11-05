//
// Created by alexandre on 12/10/23.
//

#include "IsStarship.hpp"

namespace Client {

    size_t IsStarship::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsStarship");
    }

    IsStarship::IsStarship(size_t entityIdChargeAnimation) : entityIdChargeAnimation(entityIdChargeAnimation)
    {

    }

}
