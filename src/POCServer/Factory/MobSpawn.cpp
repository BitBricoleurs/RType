/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobSpawn
*/

#include "EntityFactory.hpp"
#include <cstddef>

namespace Server {

    size_t EntityFactory::spawnCancerMob(GameEngine::ComponentsContainer &container,
                                         GameEngine::EventHandler &eventHandler,
                                         Utils::Vect2 pos, bool dropPowerup) {
        try {
            LoadConfig::ConfigData config = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createCancerMob.json");

            Utils::Vect2 velocity(config.getFloat("/createCancerMob/velocity/x"), config.getFloat("/createCancerMob/velocity/y"));

            size_t entityId = createBaseMob(
                container,
                config.getInt("/createCancerMob/hitboxHeight"),
                config.getInt("/createCancerMob/hitboxWidth"),
                pos,
                velocity,
                config.getInt("/createCancerMob/maxHealth"),
                config.getInt("/createCancerMob/damageValue"),
                config.getFloat("/createCancerMob/scale")
            );

            auto shooterComp = std::make_shared<Shooter>(
                Utils::Vect2(config.getFloat("/shootingPos/x"), config.getFloat("/shootingPos/y")),
                Utils::Vect2(config.getFloat("/bulletVelocity/x"), config.getFloat("/bulletVelocity/y")),
                config.getInt("/typeBullet")
            );

            container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
            container.bindComponentToEntity(entityId, shooterComp);

            std::tuple<unsigned long, int> IdCharge = std::make_tuple(entityId, 0);
            eventHandler.scheduleEvent("SHOOT", config.getInt("/shootDelay"), IdCharge);

            if (dropPowerup) {
                auto powerUp = std::make_shared<IsPowerUp>();
                container.bindComponentToEntity(entityId, powerUp);
            }

            std::vector<size_t> ids = {entityId};
            std::vector<std::any> args = {static_cast<int>(MobType::CANCER)};
            args.emplace_back(static_cast<int>(pos.x * 1000));
            args.emplace_back(static_cast<int>(pos.y * 1000));
            args.emplace_back(static_cast<int>(velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity.y * 1000));
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_MOB", ids, "INT", args);
            std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
            return entityId;
            } catch(const std::runtime_error& e) {
            std::cerr << "Error in spawnCancerMob: " << e.what() << std::endl;
            exit(1);
        }
    }

    size_t EntityFactory::spawnPataPataMob(GameEngine::ComponentsContainer &container,
                                           GameEngine::EventHandler &eventHandler,
                                           Utils::Vect2 pos, bool dropPowerup) {
        try {
            LoadConfig::ConfigData config = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPatapataMob.json");

            Utils::Vect2 velocity(config.getFloat("/createPatapataMob/velocity/x"), config.getFloat("/createPatapataMob/velocity/y"));

            size_t entityId = createBaseMob(
                container,
                config.getInt("/createPatapataMob/hitboxHeight"),
                config.getInt("/createPatapataMob/hitboxWidth"),
                pos,
                velocity,
                config.getInt("/createPatapataMob/maxHealth"),
                config.getInt("/createPatapataMob/damageValue"),
                config.getFloat("/createPatapataMob/scale")
            );

            container.bindComponentToEntity(entityId, std::make_shared<PataPata>());
            container.bindComponentToEntity(
                entityId,
                std::make_shared<HeightVariation>(
                    config.getFloat("/heightVarience"),
                    config.getFloat("/maxVar"),
                    pos.y
                )
            );

            std::vector<size_t> ids = {entityId};
            std::vector<std::any> args = {static_cast<int>(MobType::PATAPATA)};
            args.emplace_back(static_cast<int>(pos.x * 1000));
            args.emplace_back(static_cast<int>(pos.y * 1000));
            args.emplace_back(static_cast<int>(velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity.y * 1000));
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_MOB", ids, "INT", args);
            std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allUserMsg);

            if (dropPowerup) {
                auto powerUp = std::make_shared<IsPowerUp>();
                container.bindComponentToEntity(entityId, powerUp);
            }


            return entityId;
            }  catch(const std::runtime_error& e) {
            std::cerr << "Error in spawnPataPataMob: " << e.what() << std::endl;
            exit(1);
        }
    }

    size_t EntityFactory::spawnBugMob(GameEngine::ComponentsContainer &container,
                                      GameEngine::EventHandler &eventHandler,
                                      Utils::Vect2 pos, bool dropPowerup, std::vector<Utils::Vect2> pathPoints) {
        try {
            LoadConfig::ConfigData config = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createBugMob.json");

            Utils::Vect2 velocity(config.getFloat("/createBugMob/velocity/x"), config.getFloat("/createBugMob/velocity/y"));

            size_t entityId = createBaseMob(
                container,
                config.getInt("/createBugMob/hitboxHeight"),
                config.getInt("/createBugMob/hitboxWidth"),
                pos,
                velocity,
                config.getInt("/createBugMob/maxHealth"),
                config.getInt("/createBugMob/damageValue"),
                config.getFloat("/createBugMob/scale")
            );

            auto bug = std::make_shared<Bug>();
            if (pathPoints.empty()) {
                pathPoints = generatePathPoints();
            }
            bug->directionChangePoints = pathPoints;
            bug->currentDestinationI = 0;

            container.bindComponentToEntity(entityId, bug);

            std::vector<size_t> ids = {entityId};
            std::vector<std::any> args = {static_cast<int>(MobType::BUG)};
            args.emplace_back(static_cast<int>(pos.x * 1000));
            args.emplace_back(static_cast<int>(pos.y * 1000));
            args.emplace_back(static_cast<int>(velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity.y * 1000));
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_MOB", ids, "INT", args);
            std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allUserMsg);

            if (dropPowerup) {
                auto powerUp = std::make_shared<IsPowerUp>();
                container.bindComponentToEntity(entityId, powerUp);
            }

            eventHandler.scheduleEvent("BugSystem", 1, entityId);


            return entityId;
            } catch(const std::runtime_error& e) {
            std::cerr << "Error in spawnBugMob: " << e.what() << std::endl;
            exit(1);
        }
    }
    
    std::vector<size_t> EntityFactory::spawnBugGroup(GameEngine::ComponentsContainer &container,
                                      GameEngine::EventHandler &eventHandler,
                                      Utils::Vect2 pos, bool dropPowerup) {

        std::vector<size_t> bugGroup;

        auto pathPoints = generatePathPoints();

        float offset = 0;
        
        for (int i = 0; i < 5; i++) {
            Utils::Vect2 newPos(pos.x + offset, pos.y);
            offset += 75;
            if (dropPowerup && i == 2) {
                bugGroup.push_back(spawnBugMob(container, eventHandler, newPos, true, pathPoints));
                continue;
            }
            bugGroup.push_back(spawnBugMob(container, eventHandler, newPos, false, pathPoints));
        }
        return bugGroup;
    }
}
