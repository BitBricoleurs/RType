//
// Created by Theophilus Homawoo on 12/10/2023.
//

#include "Shoot.hpp"

void Client::Shoot::update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) {
    try {
        auto event = eventHandler.getTriggeredEvent().second;
        auto [entityID, charge] = std::any_cast<std::tuple<size_t, int>>(event);

        auto positionOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto shooterOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("Shooter"));

        if (positionOptional.has_value() && shooterOptional.has_value()) {
            auto posComp = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOptional.value());
            auto shooterComp = std::dynamic_pointer_cast<Shooter>(shooterOptional.value());

            GameEngine::Vect2 shootingPosition = posComp->pos + shooterComp->shootPosition;
            size_t bullet = 0;

            if (shooterComp->typeBullet == 0) {
                bullet = createBulletType0(charge, shootingPosition, componentsContainer, eventHandler);
            } else if (shooterComp->typeBullet == 1) {
                bullet = createBulletType1(shootingPosition, componentsContainer, eventHandler);
            }

            eventHandler.queueEvent("PLAY_SOUND", bullet);
        }
    } catch (std::bad_any_cast& e) {
        std::cerr << e.what() << std::endl;
    }
}

size_t Client::Shoot::createBulletType0(int charge, const GameEngine::Vect2& shootingPosition, GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) {
    if (charge > 50) {
        GameEngine::Vect2 adjustedPosition = shootingPosition + GameEngine::Vect2(0, -15);
        return EntityFactory::getInstance().createPlayerBullet(componentsContainer, eventHandler, adjustedPosition, GameEngine::Vect2(15, 0), "assets/ShootCharge.gif", GameEngine::rect(0, 0, 80, 16));
    } else {
        return EntityFactory::getInstance().createPlayerBullet(componentsContainer, eventHandler, shootingPosition, GameEngine::Vect2(20, 0), "assets/shoot.gif", GameEngine::rect(0, 0, 16, 4));
    }
}

size_t Client::Shoot::createBulletType1(const GameEngine::Vect2& shootingPosition, GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) {
    auto players = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("Spaceship"));
    float closestDistance = std::numeric_limits<float>::max();
    GameEngine::Vect2 directionToClosestPlayer;

    for (const auto& player : players) {
        auto positionOpt = componentsContainer.getComponent(player, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto positionComp = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOpt.value());
        if (positionComp) {
            GameEngine::Vect2 directionToPlayer = positionComp->pos - shootingPosition;
            float distanceToPlayer = directionToPlayer.magnitude();
            if (distanceToPlayer < closestDistance) {
                closestDistance = distanceToPlayer;
                directionToClosestPlayer = directionToPlayer;
            }
        }
    }

    if (closestDistance < std::numeric_limits<float>::max()) {
        float maxVal = std::max(std::abs(directionToClosestPlayer.x), std::abs(directionToClosestPlayer.y));
        float scaleFactor = 6.0f / maxVal;
        auto velocity = directionToClosestPlayer * scaleFactor;
        return EntityFactory::getInstance().createBaseEnemyBullet(componentsContainer, eventHandler, shootingPosition, velocity);
    }

    return 0;
}