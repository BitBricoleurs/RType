/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BossHit
*/

#include "ComponentsType.hpp"
#include "Damage.hpp"
#include "EventHandler.hpp"
#include "Health.hpp"
#include "ISystem.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "NetworkClientId.hpp"

namespace Server {

    class BossHit : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

      private:
        void killBossNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill);
    };
}
