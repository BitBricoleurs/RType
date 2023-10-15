//
// Created by alexandre on 04/10/23.
//

#include "ForcePodSpawn.hpp"

void ForcePodSpawn::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto anyEvent = eventHandler.getTriggeredEvent();
    if (anyEvent.first == "ForcePodSpawn") {
        auto anyEventSecond = eventHandler.getTriggeredEvent().second;
        auto posY = std::any_cast<float>(anyEventSecond);
        auto entityId = componentsContainer.createEntity();

        GameEngine::ColorR tint = {255, 255, 255, 225};

        componentsContainer.bindComponentToEntity(
            entityId, std::make_shared<GameEngine::SpriteComponent>(
                          "assets/force_pod_n1.gif", GameEngine::Vect2(0, posY),
                          GameEngine::rect(0, 0, 22, 16), 10, 2.5, 0, tint));
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::AABBComponent2D>(GameEngine::Vect2(0, posY), GameEngine::Vect2(22, 16)));
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::RectangleColliderComponent2D>(GameEngine::rect(0, 0, 22, 16)));
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::VelocityComponent>(GameEngine::Vect2(3, 0)));
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::MovementComponent>());
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::PositionComponent2D>(GameEngine::Vect2(0, posY)));
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<IsForcePod>());
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<Shooter>(GameEngine::Vect2(55, -13), 0));
        eventHandler.scheduleEvent("ForcePodStop", 200, entityId);
        auto IdCharge = std::make_tuple(entityId, 0);
        eventHandler.scheduleEvent("ShootSystem", 100, IdCharge);
    } else if (anyEvent.first == "ForcePodStop") {
        eventHandler.unscheduleEvent("ForcePodStop");
        auto anyEventSecond = anyEvent.second;
        auto entityId = std::any_cast<size_t>(anyEventSecond);
        auto velocityOpt = componentsContainer.getComponent(entityId, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
        if (velocityOpt.has_value()) {
            auto velocity = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(velocityOpt.value());
            velocity->velocity.x = 0;
            velocity->velocity.y = 0;
        }
    } else if (anyEvent.first == "ForcePodFix") {
        auto anyEventSecond = anyEvent.second;
        auto entityIdPlayer = std::any_cast<size_t>(anyEventSecond);
        auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsForcePod"));
        for (const auto& entityID : entities) {
            auto forcePodOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("IsForcePod"));
            auto posForcePodOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
            auto velocityForcePodOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
            if (forcePodOpt.has_value() && posForcePodOpt.has_value() && velocityForcePodOpt.has_value()) {
                auto forcePod = std::dynamic_pointer_cast<IsForcePod>(forcePodOpt.value());
                auto posForcePod = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(posForcePodOpt.value());
                auto velocityForcePod = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(velocityForcePodOpt.value());
                velocityForcePod->velocity.x = 0;
                if (forcePod->entityId == 0) {
                    forcePod->entityId = entityIdPlayer;
                    auto entitiesPlayer = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
                    for (const auto& entityIDPlayer : entitiesPlayer) {
                        auto playerOpt = componentsContainer.getComponent(entityIDPlayer, GameEngine::ComponentsType::getComponentType("IsPlayer"));
                        auto shooterOpt = componentsContainer.getComponent(entityIDPlayer, GameEngine::ComponentsType::getComponentType("Shooter"));
                        auto posOpt = componentsContainer.getComponent(entityIDPlayer, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
                        if (playerOpt.has_value() && shooterOpt.has_value() && posOpt.has_value()) {
                            auto player = std::dynamic_pointer_cast<IsPlayer>(playerOpt.value());
                            auto shooter = std::dynamic_pointer_cast<Shooter>(shooterOpt.value());
                            auto pos = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(posOpt.value());
                            if (player->entityIdForcePod == 0) {
                                player->entityIdForcePod = entityID;
                            }
                            GameEngine::Vect2 shootingPosition(pos->pos.x + shooter->shootPosition.x, pos->pos.y + shooter->shootPosition.y - 13);
                            posForcePod->pos = shootingPosition;
                            shooter->shootPosition.x =  shooter->shootPosition.x + 45;
                        }
                    }
                }
            }
        }
    }
}
