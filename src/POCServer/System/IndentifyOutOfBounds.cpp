//
// Created by Theophilus Homawoo on 15/10/2023.
//

#include "IndentifyOutOfBounds.hpp"

void Server::IndentifyOutOfBounds::update(GameEngine::ComponentsContainer & componentsContainer, GameEngine::EventHandler & eventHandler)
{
    auto positionComponentIDS = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

    for (const auto& positionComponentID : positionComponentIDS) {
        if (_idTimer.find(positionComponentID) != _idTimer.end()) {
            _idTimer[positionComponentID] -= 1;
            if (_idTimer[positionComponentID] <= 0) {
                _idTimer.erase(positionComponentID);
            }
            continue;
        }
        auto positionOptional = componentsContainer.getComponent(positionComponentID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto isParallaxOptional = componentsContainer.getComponent(positionComponentID, GameEngine::ComponentsType::getComponentType("IsParallax"));

        if (positionOptional.has_value()) {
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionOptional.value());

            if (isParallaxOptional.has_value()) {
                auto isParallax = std::static_pointer_cast<IsParallax>(isParallaxOptional.value());
                if (isParallax->isLooping) {
                    continue;
                }
            }

            if (position) {
                if (position->pos.x < 0 - _offset || position->pos.x > _width + _offset || position->pos.y < 0 - _offset || position->pos.y > _height + _offset) {
                    _idTimer[positionComponentID] = 121;
                    eventHandler.scheduleEvent("OUT_OF_BOUNDS", 60, positionComponentID, 1);
                }
            }
        }
    }
}
