//
// Created by alexandre on 30/10/23.
//

#include "PowerUpDualShoot.hpp"

void Server::PowerUpDualShoot::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
    auto id = std::any_cast<int>(eventHandler.getTriggeredEvent().second);

    auto playerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
    auto posPlayerType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
    auto shooterType = GameEngine::ComponentsType::getComponentType("Shooter");

    auto playerOpt = componentsContainer.getComponent(id, playerType);
    auto posPlayerOpt = componentsContainer.getComponent(id, posPlayerType);
    auto shooterOpt = componentsContainer.getComponent(id, shooterType);

    if (!playerOpt.has_value() || !posPlayerOpt.has_value() || !shooterOpt.has_value())
        return;

    auto player = std::static_pointer_cast<IsPlayer>(playerOpt.value());
    auto posPlayer = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posPlayerOpt.value());
    auto shooter = std::static_pointer_cast<Shooter>(shooterOpt.value());

    EntityFactory::getInstance().spawnPowersDualShoot(componentsContainer, eventHandler, PowerType::DUALSHOOT,Utils::Vect2( posPlayer->pos.x + shooter->shootPosition.x, posPlayer->pos.y + shooter->shootPosition.y + 20), Utils::Vect2( posPlayer->pos.x + shooter->shootPosition.x, posPlayer->pos.y + shooter->shootPosition.y - 10));
    } catch (const std::bad_any_cast &e) {
        std::cout << "Error in PowerUpDualShoot : " << e.what() << std::endl;
    }
}
