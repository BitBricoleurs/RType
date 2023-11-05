//
// Created by clagasse on 11/1/23.
//

#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "ComponentsType.hpp"
#include "IsPlayer.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "UserGameMode.hpp"
#include "EventHandler.hpp"
#include "EntityFactory.hpp"

namespace Client {
    class RevivePlayer : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
        private:
    };

}

