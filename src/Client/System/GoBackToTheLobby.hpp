//
// Created by clagasse on 11/1/23.
//

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "SpriteComponent.hpp"
#include "UserMessage.hpp"
#include "Message.hpp"
#include "GameState.hpp"

namespace Client {

    class GoBackToTheLobby : public GameEngine::ISystem {
    public:
        GoBackToTheLobby() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}
