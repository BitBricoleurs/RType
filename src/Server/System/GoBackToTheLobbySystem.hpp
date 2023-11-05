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
#include "Score.hpp"

namespace Server {
    class GoBackToTheLobbySystem : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
        void resetScoreNetwork(GameEngine::ComponentsContainer &componentsContainer,
                                           GameEngine::EventHandler &eventHandler);
        void updateScoreNetwork(GameEngine::EventHandler &eventHandler, size_t score);
    };
}
