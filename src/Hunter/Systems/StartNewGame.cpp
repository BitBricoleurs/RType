/*
** EPITECH PROJECT, 2023
** RType
** File description:
** StartNewGame
*/

#include "StartNewGame.hpp"

void StartNewGame::update(GameEngine::ComponentsContainer &componentsContainer,
                          GameEngine::EventHandler &eventHandler) {
    eventHandler.scheduleEvent("spawnBird", 75);

    try {
        size_t entityID = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

        componentsContainer.deleteEntity(entityID);

        auto scoreId = componentsContainer.getEntityWithUniqueComponent(
            GameEngine::ComponentsType::getComponentType("Score"));
        auto scoreOpt = componentsContainer.getComponent(
            scoreId, GameEngine::ComponentsType::getComponentType("Score"));

        auto baseVelocityOpt = componentsContainer.getComponent(
            scoreId, GameEngine::ComponentsType::getComponentType("BaseVelocity"));

        if (!scoreOpt.has_value() || !baseVelocityOpt.has_value())
            return;

        auto score = std::static_pointer_cast<Score>(scoreOpt.value());
        score->missed = 0;
        score->_score = 0;

        auto baseVelocity =
            std::static_pointer_cast<BaseVelocity>(baseVelocityOpt.value());
        baseVelocity->velocity.x = 6;
    } catch (const std::bad_any_cast&) {
        std::cerr << "Cast error in StartNewGame::update" << std::endl;
    }
}
