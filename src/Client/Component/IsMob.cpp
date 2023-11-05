//
// Created by alexandre on 03/10/23.
//

#include "IsMob.hpp"

namespace Client {

    size_t IsMob::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsMob");
    }

}
