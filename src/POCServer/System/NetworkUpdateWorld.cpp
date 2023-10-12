//
// Created by Clément Lagasse on 09/10/2023.
//

#include "NetworkUpdateWorld.hpp"

void NetworkUpdateWorld::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

    auto positionType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
    auto velocityType = GameEngine::ComponentsType::getComponentType("VelocityComponent");

    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    EntityFactory &factory = EntityFactory::getInstance();
    // Creating Players
    // TODO : Add player type and add PlayerNumber into creation
    for (auto &player : players) {
        if (player == entityId)
            continue;

        ids.push_back(player);
    }
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_USER", ids, "", args);
    std::shared_ptr<Network::UserMessage> userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
    eventHandler.queueEvent("SEND_NETWORK", userMessage);

    ids.clear();
    args.clear();
    // Creating Mobs
    int typeMob = static_cast<int>(MobType::CANCER);
    args.push_back(typeMob);
    for (auto &mob : mobs) {
        ids.push_back(mob);
    }
    message = std::make_shared<Network::Message>("CREATED_MOB", ids, "INT", args);
    userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
    eventHandler.queueEvent("SEND_NETWORK", userMessage);

    ids.clear();
    args.clear();
    // Creating Bullets
    for (auto &bullet : bullets) {
        auto compIsBullet = std::static_pointer_cast<IsBullet>(componentsContainer.getComponent(bullet, bulletType).value());
        args.push_back(compIsBullet->playerBullet);
        ids.push_back(bullet);
    }
    message = std::make_shared<Network::Message>("CREATED_BULLET", ids, "INT", args);
    userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
    eventHandler.queueEvent("SEND_NETWORK", userMessage);

    ids.clear();
    args.clear();
    // Updating Players (position, velocity)
    for (auto &player:  players) {
        auto compPos = std::static_pointer_cast<GameEngine::PositionComponent2D>(componentsContainer.getComponent(player, positionType).value());
        args.push_back(compPos->pos.x);
        args.push_back(compPos->pos.y);
        ids.push_back(player);
        message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
        userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
        args.clear();
        ids.clear();
        auto compVel = std::static_pointer_cast<GameEngine::VelocityComponent>(componentsContainer.getComponent(player, velocityType).value());
        args.push_back(compVel->velocity.x);
        args.push_back(compVel->velocity.y);
        ids.push_back(player);
        message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
        userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
        args.clear();
        ids.clear();
    }
    // Updating Mobs (position, velocity)
    for (auto &mob:  mobs) {
        auto compPos = std::static_pointer_cast<GameEngine::PositionComponent2D>(componentsContainer.getComponent(mob, positionType).value());
        args.push_back(compPos->pos.x);
        args.push_back(compPos->pos.y);
        ids.push_back(mob);
        message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
        userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
        args.clear();
        ids.clear();
        auto compVel = std::static_pointer_cast<GameEngine::VelocityComponent>(componentsContainer.getComponent(mob, velocityType).value());
        args.push_back(compVel->velocity.x);
        args.push_back(compVel->velocity.y);
        ids.push_back(mob);
        message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
        userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
        args.clear();
        ids.clear();
    }
    // Updating Bullets (position, velocity)
    for (auto &bullet:  bullets) {
        auto compPos = std::static_pointer_cast<GameEngine::PositionComponent2D>(componentsContainer.getComponent(bullet, positionType).value());
        args.push_back(compPos->pos.x);
        args.push_back(compPos->pos.y);
        ids.push_back(bullet);
        message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
        userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
        args.clear();
        ids.clear();
        auto compVel = std::static_pointer_cast<GameEngine::VelocityComponent>(componentsContainer.getComponent(bullet, velocityType).value());
        args.push_back(compVel->velocity.x);
        args.push_back(compVel->velocity.y);
        ids.push_back(bullet);
        message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
        userMessage = std::make_shared<Network::UserMessage>(netIdComp->id, message);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
        args.clear();
        ids.clear();
    }
}