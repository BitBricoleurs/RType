//
// Created by alexandre on 03/10/23.
//

#include "Damage.hpp"

namespace Server {

    Damage::Damage(int damageValue) : damageValue(damageValue) {}

    size_t Damage::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("Damage");
    }
}
