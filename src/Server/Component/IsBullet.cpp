//
// Created by alexandre on 03/10/23.
//

#include "IsBullet.hpp"

namespace Server {

    IsBullet::IsBullet(bool playerBullet) : playerBullet(playerBullet) {}

    size_t IsBullet::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsBullet");
    }
}
