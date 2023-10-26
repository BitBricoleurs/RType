//
// Created by alexandre on 04/10/23.
//

#include "ForcePodSpawn.hpp"

namespace Server {

    void ForcePodSpawn::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        auto anyEvent = eventHandler.getTriggeredEvent();
        if (anyEvent.first == "ForcePodSpawn") {
            auto anyEventSecond = eventHandler.getTriggeredEvent().second;
            auto posY = std::any_cast<float>(anyEventSecond);
            size_t entityId = EntityFactory::getInstance().spawnForcePod(componentsContainer, eventHandler, Utils::Vect2(-100, posY));
            eventHandler.scheduleEvent("ForcePodStop", 200, entityId, 1);
            auto IdCharge = std::make_tuple(entityId, 0);
            eventHandler.scheduleEvent("SHOOT", 100, IdCharge);
        } else if (anyEvent.first == "ForcePodStop") {
            auto anyEventSecond = anyEvent.second;
            auto entityId = std::any_cast<size_t>(anyEventSecond);
            auto velocityOpt = componentsContainer.getComponent(entityId, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
            if (velocityOpt.has_value()) {
                auto velocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(velocityOpt.value());
                velocity->velocity.x = 0;
                velocity->velocity.y = 0;
                EntityFactory::getInstance().updateEntityNetworkWithVelocity(eventHandler, entityId, velocity->velocity);
            }
        } else if (anyEvent.first == "ForcePodFix") {
            auto Ids = std::any_cast<std::tuple<size_t, size_t>>(anyEvent.second);
            auto playerId = std::get<0>(Ids);
            auto forcePodId = std::get<1>(Ids);
            auto isPlayer = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
            auto shooter = std::dynamic_pointer_cast<Shooter>(componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("Shooter")).value());
            auto posPlayer = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
            auto posForcePod = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(forcePodId, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
            auto forcePod = std::dynamic_pointer_cast<IsForcePod>(componentsContainer.getComponent(forcePodId, GameEngine::ComponentsType::getComponentType("IsForcePod")).value());
            auto forcePodVelocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(forcePodId, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
            if (isPlayer->entityIdForcePod == 0) {
                forcePodVelocity->velocity.x = 0;
                isPlayer->entityIdForcePod = forcePodId;
                forcePod->entityId = playerId;
                Utils::Vect2 shootingPosition(posPlayer->pos.x + shooter->shootPosition.x, posPlayer->pos.y + shooter->shootPosition.y - 13);
                posForcePod->pos = shootingPosition;
                shooter->shootPosition.x =  shooter->shootPosition.x + 45;
                EntityFactory::getInstance().updateEntityNetwork(eventHandler, forcePodId, posForcePod->pos, forcePodVelocity->velocity);

                auto netInterfaceId = std::dynamic_pointer_cast<NetworkClientId>(componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("NetworkClientId")).value())->id;
                std::vector<size_t> ids = {playerId};
                std::vector<std::any> args = {static_cast<int>(playerId), static_cast<int>(forcePodId)};
                std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("SYNC_FORCE_POD_PLAYER", ids, "INT", args, true);
                std::shared_ptr<Network::UserMessage> notMessage = std::make_shared<Network::UserMessage>(netInterfaceId, message);
                eventHandler.queueEvent("SEND_NETWORK", notMessage);
            }
        }
    }
}
