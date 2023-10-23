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
        auto parallaxType = GameEngine::ComponentsType::getComponentType("IsParallax");

        auto players = componentsContainer.getEntitiesWithComponent(playersType);
        auto mobs = componentsContainer.getEntitiesWithComponent(mobType);
        auto bullets = componentsContainer.getEntitiesWithComponent(bulletType);
        auto parallax = componentsContainer.getEntitiesWithComponent(parallaxType);

        auto positionType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
        auto velocityType = GameEngine::ComponentsType::getComponentType("VelocityComponent");

        std::vector<size_t> ids = {};
        std::vector<std::any> args = {};

        std::shared_ptr<Network::Message> message;
        std::shared_ptr<Network::AllUsersMessage> userMessage;
        // Updating Players (position, velocity)
        for (auto &player:  players) {
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(player, positionType).value());
            args = {compPos->pos.x, compPos->pos.y};
            ids.push_back(player);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
            auto compVel = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(player, velocityType).value());
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
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(mob, positionType).value());
            args.emplace_back(compPos->pos.x);
            args.emplace_back(compPos->pos.y);
            ids.push_back(mob);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
            auto compVel = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(mob, velocityType).value());
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
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(bullet, positionType).value());
            args.emplace_back(compPos->pos.x);
            args.emplace_back(compPos->pos.y);
            ids.push_back(bullet);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
            auto compVel = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(bullet, velocityType).value());
            args.emplace_back(compVel->velocity.x);
            args.emplace_back(compVel->velocity.y);
            ids.push_back(bullet);
            message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
        }
        // Updating Parallax (position, velocity)
        for (auto &para:  parallax) {
            if (!componentsContainer.getComponent(para, parallaxType).has_value())
                continue;
            auto compPos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(para, positionType).value());
            args.emplace_back(compPos->pos.x);
            args.emplace_back(compPos->pos.y);
            ids.push_back(para);
            message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
            if (!componentsContainer.getComponent(para, velocityType).has_value())
                continue;
            auto compVel = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(para, velocityType).value());
            args.emplace_back(compVel->velocity.x);
            args.emplace_back(compVel->velocity.y);
            ids.push_back(para);
            std::cout << "parallax velocity: " << compVel->velocity.x << std::endl;
            message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
            userMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
        }
    }
}
