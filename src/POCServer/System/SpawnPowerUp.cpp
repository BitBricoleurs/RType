//
// Created by Bartosz on 10/10/23.
//

#include "SpawnPowerUp.hpp"

namespace Server {

    void SpawnPowerUp::update(GameEngine::ComponentsContainer &componentsContainer,
                              GameEngine::EventHandler &eventHandler) {
        try {
            auto pos = std::any_cast<Utils::Vect2>(eventHandler.getTriggeredEvent().second);
            EntityFactory::getInstance().spawnPowerUp(componentsContainer, eventHandler, pos, PowerUpType::INVOLVE);
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from SpawnPowerUp System " << e.what() << std::endl;
        }
    }
}
