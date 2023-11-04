//
// Created by clagasse on 11/1/23.
//

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "UserMessage.hpp"
#include "Message.hpp"
#include "GameState.hpp"
#include "SpriteComponent.hpp"

namespace Client {

    class GameOverSystem : public GameEngine::ISystem {
    public:
        GameOverSystem() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}
