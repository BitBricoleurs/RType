//
// Created by clagasse on 11/1/23.
//

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "GameState.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"

namespace Server {
    class GoBackToTheLobbySystem : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}
