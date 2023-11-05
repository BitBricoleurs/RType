//
// Created by alexandre on 03/10/23.
//

#include "IsBoss.hpp"

namespace Server {

    size_t IsBoss::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("IsBoss");
    }
}
