//
// Created by alexandre on 30/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "SpriteComponent.hpp"
#include "Message.hpp"
#include "IsPlayer.hpp"

namespace Client {

    class ForcePodUpgrade : public GameEngine::ISystem {
    public:
        ForcePodUpgrade() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}
