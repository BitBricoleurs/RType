//
// Created by Clément Lagasse on 13/10/2023.
//

#include "NetworkCreateWorld.hpp"

namespace Server {

    void NetworkCreateWorld::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        auto &server = Network::Server::getInstance();

        size_t entityId = 0;

        try {
            entityId = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkClientConnect System " << e.what() << std::endl;
            return;
        }

        auto networkIdType = GameEngine::ComponentsType::getComponentType("NetworkClientId");
        auto mayComp = componentsContainer.getComponent(entityId, networkIdType);
        if (!mayComp.has_value())
            return;
        auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());

        auto playersType = GameEngine::ComponentsType::getComponentType("IsPlayer");
        auto mobType = GameEngine::ComponentsType::getComponentType("IsMob");
        auto bulletType = GameEngine::ComponentsType::getComponentType("IsBullet");
        auto parallaxType = GameEngine::ComponentsType::getComponentType("IsParallax");
        auto powerType = GameEngine::ComponentsType::getComponentType("IsPower");
        auto forcePodType = GameEngine::ComponentsType::getComponentType("IsForcePod");

        auto players = componentsContainer.getEntitiesWithComponent(playersType);
        auto mobs = componentsContainer.getEntitiesWithComponent(mobType);
        auto bullets = componentsContainer.getEntitiesWithComponent(bulletType);
        auto parallax = componentsContainer.getEntitiesWithComponent(parallaxType);
        auto powers = componentsContainer.getEntitiesWithComponent(powerType);
        auto forcePods = componentsContainer.getEntitiesWithComponent(forcePodType);

        auto mobTypeCompCancer = GameEngine::ComponentsType::getComponentType("Cancer");
        auto mobTypeCompPataPata = GameEngine::ComponentsType::getComponentType("PataPata");
        auto bossTypeComp = GameEngine::ComponentsType::getComponentType("Boss");

        auto positionType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
        auto velocityType = GameEngine::ComponentsType::getComponentType("VelocityComponent");

        std::vector<size_t> ids = {};
        std::vector<std::any> args = {};
        EntityFactory &factory = EntityFactory::getInstance();
        std::shared_ptr<Network::Message> message = nullptr;
        std::shared_ptr<Network::UserMessage> userMessage = nullptr;

        // Creating Players
        for (auto &player : players) {
            PlayerNumber numb = factory.getPlayerMap().at(player);
            if (player == entityId)
                continue;
            args.emplace_back(static_cast<int>(numb));
            ids.push_back(player);
            auto mayPosition = componentsContainer.getComponent(player, positionType);
            if (!mayPosition.has_value())
                continue;
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayPosition.value());
            args.emplace_back(static_cast<int>(position->pos.x * 1000));
            args.emplace_back(static_cast<int>(position->pos.y * 1000));
            auto mayVelocity = componentsContainer.getComponent(player, velocityType);
            if (!mayVelocity.has_value())
                continue;
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayVelocity.value());
            args.emplace_back(static_cast<int>(velocity->velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity->velocity.y * 1000));
            message = std::make_shared<Network::Message>("CREATED_USER", ids, "INT", args);
            userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            args.clear();
            ids.clear();
        }

        // Creating Mobs
        int typeMob = static_cast<int>(MobType::CANCER);
        for (auto &mob : mobs) {
            if (componentsContainer.getComponent(mob, mobTypeCompCancer).has_value()) {
                typeMob = static_cast<int>(MobType::CANCER);
            } else if (componentsContainer.getComponent(mob, mobTypeCompPataPata).has_value()) {
                typeMob = static_cast<int>(MobType::PATAPATA);
            }
            else if (componentsContainer.getComponent(mob, bossTypeComp).has_value()) {
                typeMob = static_cast<int>(MobType::BOSS);
            }
            else {
                continue;
            }
            ids.push_back(mob);
            args.emplace_back(typeMob);
            auto mayPosition = componentsContainer.getComponent(mob, positionType);
            if (!mayPosition.has_value())
                continue;
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayPosition.value());
            args.emplace_back(static_cast<int>(position->pos.x * 1000));
            args.emplace_back(static_cast<int>(position->pos.y * 1000));
            auto mayVelocity = componentsContainer.getComponent(mob, velocityType);
            if (!mayVelocity.has_value())
                continue;
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayVelocity.value());
            args.emplace_back(static_cast<int>(velocity->velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity->velocity.y * 1000));
            message = std::make_shared<Network::Message>("CREATED_MOB", ids, "INT", args);
            userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            ids.clear();
            args.clear();
        }


        // Creating Bullets
        for (auto &bullet : bullets) {
            auto compIsBullet = std::static_pointer_cast<IsBullet>(componentsContainer.getComponent(bullet, bulletType).value());
            args.emplace_back(compIsBullet->playerBullet);
            ids.push_back(bullet);
            auto mayPosition = componentsContainer.getComponent(bullet, positionType);
            if (!mayPosition.has_value())
                continue;
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayPosition.value());
            args.emplace_back(static_cast<int>(position->pos.x * 1000));
            args.emplace_back(static_cast<int>(position->pos.y * 1000));
            auto mayVelocity = componentsContainer.getComponent(bullet, velocityType);
            if (!mayVelocity.has_value())
                continue;
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayVelocity.value());
            args.emplace_back(static_cast<int>(velocity->velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity->velocity.y * 1000));
            message = std::make_shared<Network::Message>("CREATED_BULLET", ids, "INT", args);
            userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            ids.clear();
            args.clear();
        }

        // Creating Parallax
        for (auto &para : parallax) {
            if (!componentsContainer.getComponent(para, parallaxType).has_value())
                continue;
            auto compIsParallax = std::static_pointer_cast<IsParallax>(componentsContainer.getComponent(para, parallaxType).value());
            auto posParallax = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(para, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
            auto velocityParallax = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(para, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
            args.emplace_back(static_cast<int>(compIsParallax->type));
            args.emplace_back(static_cast<int>(posParallax->pos.x * 1000));
            args.emplace_back(static_cast<int>(posParallax->pos.y * 1000));
            args.emplace_back(static_cast<int>(velocityParallax->velocity.x * 1000));
            args.emplace_back(static_cast<int>(compIsParallax->layer));
            ids.push_back(para);
            message = std::make_shared<Network::Message>("CREATE_PARALLAX", ids, "INT", args);
            userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            ids.clear();
            args.clear();
        }
        // Creating Powers
        for(auto &power : powers) {
            auto compIsPower = std::static_pointer_cast<IsPower>(componentsContainer.getComponent(power, powerType).value());
            args.push_back(static_cast<int>(compIsPower->type));
            ids.push_back(power);
            auto mayPosition = componentsContainer.getComponent(power, positionType);
            if (!mayPosition.has_value())
                continue;
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayPosition.value());
            args.emplace_back(static_cast<int>(position->pos.x * 1000));
            args.emplace_back(static_cast<int>(position->pos.y * 1000));
            auto mayVelocity = componentsContainer.getComponent(power, velocityType);
            if (!mayVelocity.has_value())
                continue;
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayVelocity.value());
            args.emplace_back(static_cast<int>(velocity->velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity->velocity.y * 1000));
            message = std::make_shared<Network::Message>("CREATED_POWERUP", ids, "INT", args);
            userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            ids.clear();
            args.clear();
        }

        // Creating ForcePods
        for(auto &forcePod : forcePods) {
            ids.push_back(forcePod);
            auto mayPosition = componentsContainer.getComponent(forcePod, positionType);
            if (!mayPosition.has_value())
                continue;
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayPosition.value());
            args.emplace_back(static_cast<int>(position->pos.x * 1000));
            args.emplace_back(static_cast<int>(position->pos.y * 1000));
            auto mayVelocity = componentsContainer.getComponent(forcePod, velocityType);
            if (!mayVelocity.has_value())
                continue;
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayVelocity.value());
            args.emplace_back(static_cast<int>(velocity->velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity->velocity.y * 1000));
            message = std::make_shared<Network::Message>("CREATED_FORCEPOD", ids, "INT", args);
            userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            ids.clear();
            args.clear();
        }
        eventHandler.queueEvent("UPDATE_WORLD");
    }
}
