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

        if (positionOptional.has_value()) {
            auto position = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOptional.value());

            if (position) {
                if (position->pos.x < 0 - _offset || position->pos.x > _width + _offset || position->pos.y < 0 - _offset || position->pos.y > _height + _offset) {
                    _idTimer[positionComponentID] = 121;
                    std::cout << "OUT OF BOUNDS" << std::endl;
                    eventHandler.scheduleEvent("OUT_OF_BOUNDS", 120, positionComponentID, 1);
                }
            }
        }
    }
}
