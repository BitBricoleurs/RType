//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreateMob.hpp"

void CreateMob::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
        try {
            auto message = eventHandler.getTriggeredEvent().second;
            auto messageData = std::any_cast<std::shared_ptr<Network::Message>>(message);

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();

            if (ids.size() != 1)
                return;

            MobType typeMob = static_cast<MobType>(std::any_cast<int>(args[0]));
            EntityFactory  &factory = EntityFactory::getInstance();
            GameEngine::Vect2 pos = {0, 0};

            size_t entityId = 0;
            if (typeMob == MobType::CANCER) {
                entityId = factory.spawnCancerMob(componentsContainer, eventHandler, pos, 0);
            } else if (typeMob == MobType::PATAPATA) {
                entityId = factory.spawnPataPataMob(componentsContainer, eventHandler, pos, 0);
            } else {
                entityId = factory.spawnBugMob(componentsContainer, eventHandler, pos, 0);
            }
            factory.registerEntity(ids.front(), entityId);
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
}