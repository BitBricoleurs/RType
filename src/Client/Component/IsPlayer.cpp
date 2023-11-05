//
// Created by alexandre on 03/10/23.
//

#include "IsPlayer.hpp"

namespace Client {

    size_t IsPlayer::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsPlayer");
    }
    IsPlayer::IsPlayer(size_t entityIdChargeAnimation) : entityIdChargeAnimation(entityIdChargeAnimation)
    {

    }

}
