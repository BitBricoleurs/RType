//
// Created by alexandre on 04/10/23.
//

#include "ForcePodSpawn.hpp"

namespace Server {

    void ForcePodSpawn::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        try {
            auto anyEvent = eventHandler.getTriggeredEvent();
            if (anyEvent.first == "ForcePodSpawn") {
                auto anyEventSecond = eventHandler.getTriggeredEvent().second;
                auto posY = std::any_cast<float>(anyEventSecond);
                size_t entityId = EntityFactory::getInstance().spawnForcePod(componentsContainer, eventHandler, Utils::Vect2(-100, posY));
                eventHandler.scheduleEvent("ForcePodStop", 200, entityId, 1);
                std::tuple<unsigned long, int> IdCharge = std::make_tuple(entityId, 0);
                eventHandler.scheduleEvent("SHOOT", 100, IdCharge);
            } else if (anyEvent.first == "ForcePodStop") {
                auto anyEventSecond = anyEvent.second;
                auto entityId = std::any_cast<size_t>(anyEventSecond);
                auto velocityOpt = componentsContainer.getComponent(entityId, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
                if (velocityOpt.has_value()) {
                    auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityOpt.value());
                    velocity->velocity.x = 0;
                    velocity->velocity.y = 0;
                    EntityFactory::getInstance().updateEntityNetworkWithVelocity(eventHandler, entityId, velocity->velocity);
                }
            } else if (anyEvent.first == "ForcePodFix") {
                auto Ids = std::any_cast<std::tuple<size_t, size_t>>(anyEvent.second);
                auto playerId = std::get<0>(Ids);
                auto forcePodId = std::get<1>(Ids);

                auto isPlayerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
                auto shooterType = GameEngine::ComponentsType::getComponentType("Shooter");
                auto posType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
                auto forcePodType = GameEngine::ComponentsType::getComponentType("IsForcePod");
                auto forcePodVelocityType = GameEngine::ComponentsType::getComponentType("VelocityComponent");

                auto playerOpt = componentsContainer.getComponent(playerId, isPlayerType);
                auto shooterOpt = componentsContainer.getComponent(playerId, shooterType);
                auto posPlayerOpt = componentsContainer.getComponent(playerId, posType);
                auto posForcePodOpt = componentsContainer.getComponent(forcePodId, posType);
                auto forcePodOpt = componentsContainer.getComponent(forcePodId, forcePodType);
                auto forcePodVelocityOpt = componentsContainer.getComponent(forcePodId, forcePodVelocityType);

                if (!playerOpt.has_value() || !shooterOpt.has_value() || !posPlayerOpt.has_value() || !posForcePodOpt.has_value() || !forcePodOpt.has_value() || !forcePodVelocityOpt.has_value())
                    return;

                auto isPlayer = std::static_pointer_cast<IsPlayer>(playerOpt.value());
                auto shooter = std::static_pointer_cast<Shooter>(shooterOpt.value());
                auto posPlayer = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posPlayerOpt.value());
                auto posForcePod = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posForcePodOpt.value());
                auto forcePod = std::static_pointer_cast<IsForcePod>(forcePodOpt.value());
                auto forcePodVelocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(forcePodVelocityOpt.value());
                if (isPlayer->entityIdForcePod == 0) {

                    isPlayer->entityIdForcePod = forcePodId;
                    forcePod->entityId = playerId;
                    shooter->shootPosition.x =  shooter->shootPosition.x + 45;

                    auto networkType = GameEngine::ComponentsType::getComponentType("NetworkClientId");

                    auto netowrkOpt = componentsContainer.getComponent(playerId, networkType);

                    if (!netowrkOpt.has_value())
                        return;
                    auto netInterfaceId = std::static_pointer_cast<NetworkClientId>(netowrkOpt.value())->id;
                    std::vector<size_t> ids = {playerId};
                    std::vector<std::any> args = {static_cast<int>(playerId), static_cast<int>(forcePodId)};
                    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("SYNC_FORCE_POD_PLAYER", ids, "INT", args, true);
                    std::shared_ptr<Network::UserMessage> notMessage = std::make_shared<Network::UserMessage>(netInterfaceId, message);
                    eventHandler.queueEvent("SEND_NETWORK", notMessage);
                }
            }
        } catch (const std::bad_any_cast &e) {
            std::cout << "Error in ForcePodSpawn : " << e.what() << std::endl;
        }
    }
}
