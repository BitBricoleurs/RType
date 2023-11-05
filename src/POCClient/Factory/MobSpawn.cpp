/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobSpawn
*/

#include "EntityFactory.hpp"

namespace Client {

    size_t EntityFactory::spawnCancerMob(GameEngine::ComponentsContainer &container,
                                         GameEngine::EventHandler &eventHandler,
                                         Utils::Vect2 pos, Utils::Vect2 vel) {


        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createCancerMob.json");

            size_t entityId = createBaseMob(
                container,
                data.getString("/createCancerMob/spriteSheetPath"),
                data.getInt("/createCancerMob/spriteSheetHeight"),
                data.getInt("/createCancerMob/spriteSheetWidth"),
                data.getInt("/createCancerMob/frames"),
                data.getBool("/createCancerMob/twoDirections"),
                data.getBool("/createCancerMob/reverse"),
                data.getString("/createCancerMob/deathSpriteSheetPath"),
                data.getInt("/createCancerMob/deathSpriteSheetHeight"),
                data.getInt("/createCancerMob/deathSpriteSheetWidth"),
                data.getInt("/createCancerMob/deathFrames"),
                pos,
                vel,
                data.getInt("/createCancerMob/player"),
                data.getFloat("/createCancerMob/scale"),
                data.getFloat("/createCancerMob/rotation"),
                Utils::ColorR(
                    data.getInt("/createCancerMob/tint/r"),
                    data.getInt("/createCancerMob/tint/g"),
                    data.getInt("/createCancerMob/tint/b"),
                    data.getInt("/createCancerMob/tint/a")
                ),
                data.getInt("/createCancerMob/layer")
            );

              container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
              eventHandler.scheduleEvent("animate", 30, std::make_tuple(std::string("Cancer"), entityId));
              auto IdCharge = std::make_tuple(entityId, 0);
              eventHandler.scheduleEvent("ShootSystem", 300, IdCharge);
              return entityId;
        } catch(const std::runtime_error& e) {
            std::cerr << "Error in createCancerMob: " << e.what() << std::endl;
            exit(1);
        }
    }

    size_t
    EntityFactory::spawnPataPataMob(GameEngine::ComponentsContainer &container,
                                    GameEngine::EventHandler &eventHandler,
                                    Utils::Vect2 pos, Utils::Vect2 vel) {
        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPatapataMob.json");

            size_t entityId = createBaseMob(
                container,
                data.getString("/createPatapataMob/spriteSheetPath"),
                data.getInt("/createPatapataMob/spriteSheetHeight"),
                data.getInt("/createPatapataMob/spriteSheetWidth"),
                data.getInt("/createPatapataMob/frames"),
                data.getBool("/createPatapataMob/twoDirections"),
                data.getBool("/createPatapataMob/reverse"),
                data.getString("/createPatapataMob/deathSpriteSheetPath"),
                data.getInt("/createPatapataMob/deathSpriteSheetHeight"),
                data.getInt("/createPatapataMob/deathSpriteSheetWidth"),
                data.getInt("/createPatapataMob/deathFrames"),
                pos,
                vel,
                data.getInt("/createPatapataMob/player"),
                data.getFloat("/createPatapataMob/scale"),
                data.getFloat("/createPatapataMob/rotation"),
                Utils::ColorR(
                    data.getInt("/createPatapataMob/tint/r"),
                    data.getInt("/createPatapataMob/tint/g"),
                    data.getInt("/createPatapataMob/tint/b"),
                    data.getInt("/createPatapataMob/tint/a")
                ),
                data.getInt("/createPatapataMob/layer")
            );
            container.bindComponentToEntity(entityId, std::make_shared<PataPata>());

          eventHandler.scheduleEvent(
              "animate", 10, std::make_tuple(std::string("PataPata"), entityId));
          return entityId;
        } catch(const std::runtime_error& e) {
            std::cerr << "Error in createPataptaMob: " << e.what() << std::endl;
            exit(1);
        }
    }

    size_t EntityFactory::spawnBugMob(GameEngine::ComponentsContainer &container,
                                      GameEngine::EventHandler &eventHandler,
                                      Utils::Vect2 pos, Utils::Vect2 vel)
                                      {
        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createBugMob.json");

        size_t entityId = createBaseMob(
            container,
            data.getString("/createBugMob/spriteSheetPath"),
            data.getInt("/createBugMob/spriteSheetHeight"),
            data.getInt("/createBugMob/spriteSheetWidth"),
            data.getInt("/createBugMob/frames"),
            data.getBool("/createBugMob/twoDirections"),
            data.getBool("/createBugMob/reverse"),
            data.getString("/createBugMob/deathSpriteSheetPath"),
            data.getInt("/createBugMob/deathSpriteSheetHeight"),
            data.getInt("/createBugMob/deathSpriteSheetWidth"),
            data.getInt("/createBugMob/deathFrames"),
            pos,
            vel,
            data.getInt("/createBugMob/player"),
            data.getFloat("/createBugMob/scale"),
            data.getFloat("/createBugMob/rotation"),
            Utils::ColorR(
                data.getInt("/createBugMob/tint/r"),
                data.getInt("/createBugMob/tint/g"),
                data.getInt("/createBugMob/tint/b"),
                data.getInt("/createBugMob/tint/a")
            ),
            data.getInt("/createBugMob/layer")
        );
          container.bindComponentToEntity(entityId, std::make_shared<Bug>());

          return entityId;
        }  catch(const std::runtime_error& e) {
            std::cerr << "Error in createBugMob: " << e.what() << std::endl;
            exit(1);
        }
    }

}
