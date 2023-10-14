/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateNewBullet
*/

#include "EntityFactory.hpp"

size_t
EntityFactory::createPlayerBullet(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos, GameEngine::Vect2 velocity, size_t typeBullet ) {
    nlohmann::json config = loadConfig("config/Entity/createBulletPlayer.json");

    nlohmann::json rectConfig = config["createBullet"]["bulletTypes"]["type" + std::to_string(typeBullet)]["rect"];
    int rectH = rectConfig["h"].get<int>();
    int rectW = rectConfig["w"].get<int>();

    size_t entityId = createBullet(
        container,
        rectH,
        rectW,
        pos,
        velocity,
        config["createBullet"]["damageValue"].get<int>(),
        config["createBullet"]["isPlayerBullet"].get<bool>(),
        config["createBullet"]["scale"].get<float>()
    );
    std::vector<size_t> ids = {entityId};
    std::vector<std::any> args = {static_cast<int>(BulletOwner::PLAYER)};
    if (typeBullet == 0) {
        args.push_back(static_cast<int>(BulletType::NORMAL));
    } else if (typeBullet == 1) {
        std::cout << "CHARGED" << std::endl;
        args.push_back(static_cast<int>(BulletType::CHARGED));
    }
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_BULLET", ids, "INT", args);
    std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
    eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
    EntityFactory::updateEntityNetwork(eventHandler, entityId, pos, velocity);
    return entityId;
}

size_t
EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos, GameEngine::Vect2 velocity) {

    nlohmann::json config = loadConfig("config/Entity/createBulletEnemy.json");

    size_t entityId = createBullet(
    container,
    config["createBullet"]["hitboxheight"].get<int>(),
    config["createBullet"]["hitboxWidth"].get<int>(),
    pos,
    velocity,
    config["createBullet"]["damageValue"].get<int>(),
    config["createBullet"]["isPlayerBullet"].get<bool>(),
    config["createBullet"]["scale"].get<float>()
    );
  return entityId;
}
