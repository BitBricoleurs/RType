//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreateBullet.hpp"

void CreateBullet::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto message = eventHandler.getTriggeredEvent().second;
    auto messageData = std::any_cast<std::shared_ptr<Network::Message>>(message);

    std::vector<size_t> ids = messageData->getIDs();
    std::vector<std::any> args = messageData->getArgs();

    if (ids.size() != 1)
        return;

    BulletOwner number = static_cast<BulletOwner>(std::any_cast<int>(args[0]));
    EntityFactory  &factory = EntityFactory::getInstance();
    GameEngine::Vect2 pos = {0, 0};
    size_t entityId = 0;
    std::string path = "";
    GameEngine::Vect2 velocity = {0, 0};
    GameEngine::rect rect = {0, 0, 0, 0};
    if (number == BulletOwner::PLAYER)
        entityId = factory.createPlayerBullet(componentsContainer, eventHandler, pos, velocity, number);
    else
        //entityId = factory.createEnemyBullet(componentsContainer, eventHandler, pos, number);
    factory.registerEntity(ids.front(), entityId);
}