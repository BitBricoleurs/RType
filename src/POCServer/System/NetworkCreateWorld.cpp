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

        auto players = componentsContainer.getEntitiesWithComponent(playersType);
        auto mobs = componentsContainer.getEntitiesWithComponent(mobType);
        auto bullets = componentsContainer.getEntitiesWithComponent(bulletType);

        auto mobTypeCompCancer = GameEngine::ComponentsType::getComponentType("Cancer");
        auto mobTypeCompPataPata = GameEngine::ComponentsType::getComponentType("PataPata");
        auto bossTypeComp = GameEngine::ComponentsType::getComponentType("Boss");

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
            args.push_back(static_cast<int>(numb));
            ids.push_back(player);
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
            args.push_back(typeMob);
            message = std::make_shared<Network::Message>("CREATED_MOB", ids, "INT", args);
            userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            ids.clear();
            args.clear();
        }


        // Creating Bullets
        for (auto &bullet : bullets) {
            auto compIsBullet = std::static_pointer_cast<IsBullet>(componentsContainer.getComponent(bullet, bulletType).value());
            args.push_back(compIsBullet->playerBullet);
            ids.push_back(bullet);
            message = std::make_shared<Network::Message>("CREATED_BULLET", ids, "INT", args);
            userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
            eventHandler.queueEvent("SEND_NETWORK", userMessage);
            ids.clear();
            args.clear();
        }
        eventHandler.queueEvent("UPDATE_WORLD");
    }
}
