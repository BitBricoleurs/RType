//
// Created by Clément Lagasse on 09/10/2023.
//

#include "NetworkUpdateWorld.hpp"

namespace Server {

    void NetworkUpdateWorld::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        auto &server = Network::Server::getInstance();

        auto playersType = GameEngine::ComponentsType::getComponentType("IsPlayer");
        auto mobType = GameEngine::ComponentsType::getComponentType("IsMob");
        auto bulletType = GameEngine::ComponentsType::getComponentType("IsBullet");
        auto powerType = GameEngine::ComponentsType::getComponentType("IsPower");
        auto forcePodType = GameEngine::ComponentsType::getComponentType("IsForcePod");

        auto players = componentsContainer.getEntitiesWithComponent(playersType);
        auto mobs = componentsContainer.getEntitiesWithComponent(mobType);
        auto bullets = componentsContainer.getEntitiesWithComponent(bulletType);
        auto powers = componentsContainer.getEntitiesWithComponent(powerType);
        auto forcePods = componentsContainer.getEntitiesWithComponent(forcePodType);

        auto positionType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
        auto velocityType = GameEngine::ComponentsType::getComponentType("VelocityComponent");

        std::vector<size_t> ids = {};
        std::vector<std::any> args = {};

        std::shared_ptr<Network::Message> message;
        std::shared_ptr<Network::AllUsersMessage> userMessage;
        // Updating Players (position, velocity)
        for (auto &player:  players) {
            auto mayComp = componentsContainer.getComponent(player, positionType);
            if (!mayComp.has_value())
                continue;
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayComp.value());
            args = {compPos->pos.x, compPos->pos.y};
            ids.push_back(player);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
            auto mayComp2 = componentsContainer.getComponent(player, velocityType);
            if (!mayComp2.has_value())
                continue;
            auto compVel = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayComp2.value());
            args = {compVel->velocity.x, compVel->velocity.y};
            ids.push_back(player);
            message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
        }
        // Updating Mobs (position, velocity)
        for (auto &mob:  mobs) {
            auto mayComp = componentsContainer.getComponent(mob, positionType);
            if (!mayComp.has_value())
                continue;
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayComp.value());
            args.emplace_back(compPos->pos.x);
            args.emplace_back(compPos->pos.y);
            ids.push_back(mob);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
            auto mayComp2 = componentsContainer.getComponent(mob, velocityType);
            if (!mayComp2.has_value())
                continue;
            auto compVel = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayComp2.value());
            args.emplace_back(compVel->velocity.x);
            args.emplace_back(compVel->velocity.y);
            ids.push_back(mob);
            message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
        }
        // Updating Bullets (position, velocity)
        for (auto &bullet:  bullets) {
            auto mayComp = componentsContainer.getComponent(bullet, positionType);
            if (!mayComp.has_value())
                continue;
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayComp.value());
            args.emplace_back(compPos->pos.x);
            args.emplace_back(compPos->pos.y);
            ids.push_back(bullet);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
            auto mayComp2 = componentsContainer.getComponent(bullet, velocityType);
            if (!mayComp2.has_value())
                continue;
            auto compVel = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayComp2.value());
            args.emplace_back(compVel->velocity.x);
            args.emplace_back(compVel->velocity.y);
            ids.push_back(bullet);
            message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
        }
        // Updating Powers (position)
        for (auto &power:  powers) {
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(power, positionType).value());
            args.emplace_back(compPos->pos.x);
            args.emplace_back(compPos->pos.y);
            ids.push_back(power);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
        }
        // Updating ForcePods (position, velocity)
        for (auto &forcePod:  forcePods) {
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(forcePod, positionType).value());
            args.emplace_back(compPos->pos.x);
            args.emplace_back(compPos->pos.y);
            ids.push_back(forcePod);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
            auto compVel = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(forcePod, velocityType).value());
            args.emplace_back(compVel->velocity.x);
            args.emplace_back(compVel->velocity.y);
            ids.push_back(forcePod);
            message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
        }
    }
}
