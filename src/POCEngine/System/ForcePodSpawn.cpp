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

        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::SpriteComponent>("assets/force_pod_n1.gif", GameEngine::Vect2(0, posY), GameEngine::rect(0, 0, 22, 16), 10, 2.5, 0, GameEngine::ColorR(255, 255, 255, 225)));
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::VelocityComponent>(GameEngine::Vect2(3, 0)));
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::MovementComponent>());
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<GameEngine::PositionComponent2D>(GameEngine::Vect2(0, posY)));
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<IsForcePod>());
        componentsContainer.bindComponentToEntity(entityId, std::make_shared<Shooter>(GameEngine::Vect2(55, -13), GameEngine::Vect2(6,0), 1));
        eventHandler.scheduleEvent("ForcePodStop", 200, entityId);
        eventHandler.scheduleEvent("ShootSystem", 100, entityId);
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
        std::cout << "FIX" << std::endl;
        auto anyEventSecond = anyEvent.second;
        auto entityIdPlayer = std::any_cast<size_t>(anyEventSecond);
        std::cout << "Entity id" << entityIdPlayer << std::endl;
        auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsForcePod"));
        for (const auto& entityID : entities) {
            auto forcePodOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("IsForcePod"));
            if (forcePodOpt.has_value()) {
                auto forcePod = std::dynamic_pointer_cast<IsForcePod>(forcePodOpt.value());
                if (forcePod->entityId == 0) {
                    forcePod->entityId = entityIdPlayer;
                }
            }
        }

    }
}
