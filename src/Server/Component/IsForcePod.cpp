//
// Created by alexandre on 04/10/23.
//

#include "IsForcePod.hpp"

namespace Server {

    IsForcePod::IsForcePod()
    {
        entityId = 0;
    }

    size_t IsForcePod::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("IsForcePod");
    }
}
