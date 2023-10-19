#include "EntityFactory.hpp"
#include "LoadConfig.hpp"
#include "ConfigData.hpp"

size_t EntityFactory::spawnCancerMob(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     Utils::Vect2 pos, bool dropPowerup) {

    try {
        LoadConfig::ConfigData config = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createCancerMob.json");

        size_t entityId = createBaseMob(
            container,
            config.getString("/createCancerMob/spriteSheetPath"),
            config.getInt("/createCancerMob/spriteSheetHeight"),
            config.getInt("/createCancerMob/spriteSheetWidth"),
            config.getInt("/createCancerMob/frames"),
            config.getBool("/createCancerMob/twoDirections"),
            config.getBool("/createCancerMob/reverse"),
            config.getString("/createCancerMob/deathSpriteSheetPath"),
            config.getInt("/createCancerMob/deathSpriteSheetHeight"),
            config.getInt("/createCancerMob/deathSpriteSheetWidth"),
            config.getInt("/createCancerMob/deathFrames"),
            pos,
            Utils::Vect2(
                config.getFloat("/createCancerMob/velocity/x"),
                config.getFloat("/createCancerMob/velocity/y")
            ),
            config.getInt("/createCancerMob/maxHealth"),
            config.getInt("/createCancerMob/damageValue"),
            config.getInt("/createCancerMob/player"),
            config.getFloat("/createCancerMob/scale"),
            config.getFloat("/createCancerMob/rotation"),
            Utils::ColorR(
                config.getInt("/createCancerMob/tint/r"),
                config.getInt("/createCancerMob/tint/g"),
                config.getInt("/createCancerMob/tint/b"),
                config.getInt("/createCancerMob/tint/a")
            ),
            config.getInt("/createCancerMob/layer"),
            dropPowerup
        );

        auto shooterComp = std::make_shared<Shooter>(
            Utils::Vect2(
                config.getFloat("/shootingPos/x"),
                config.getFloat("/shootingPos/y")
            ),
            config.getInt("/typeBullet")
        );
        container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
        container.bindComponentToEntity(entityId, shooterComp);
        eventHandler.scheduleEvent("animate", 30, std::make_tuple(std::string("Cancer"), entityId));
        auto IdCharge = std::make_tuple(entityId, 0);
        eventHandler.scheduleEvent("ShootSystem", 300, IdCharge);

        return entityId;
    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createCancerMob: " << e.what() << std::endl;
        exit(1);
    }
}

size_t EntityFactory::spawnPataPataMob(GameEngine::ComponentsContainer &container,
                                       GameEngine::EventHandler &eventHandler,
                                       Utils::Vect2 pos, bool dropPowerup) {

    try {
        LoadConfig::ConfigData config = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPatapataMob.json");

        size_t entityId = createBaseMob(
            container,
            config.getString("/createPatapataMob/spriteSheetPath"),
            config.getInt("/createPatapataMob/spriteSheetHeight"),
            config.getInt("/createPatapataMob/spriteSheetWidth"),
            config.getInt("/createPatapataMob/frames"),
            config.getBool("/createPatapataMob/twoDirections"),
            config.getBool("/createPatapataMob/reverse"),
            config.getString("/createPatapataMob/deathSpriteSheetPath"),
            config.getInt("/createPatapataMob/deathSpriteSheetHeight"),
            config.getInt("/createPatapataMob/deathSpriteSheetWidth"),
            config.getInt("/createPatapataMob/deathFrames"),
            pos,
            Utils::Vect2(
                config.getFloat("/createPatapataMob/velocity/x"),
                config.getFloat("/createPatapataMob/velocity/y")
            ),
            config.getInt("/createPatapataMob/maxHealth"),
            config.getInt("/createPatapataMob/damageValue"),
            config.getInt("/createPatapataMob/player"),
            config.getFloat("/createPatapataMob/scale"),
            config.getFloat("/createPatapataMob/rotation"),
            Utils::ColorR(
                config.getInt("/createPatapataMob/tint/r"),
                config.getInt("/createPatapataMob/tint/g"),
                config.getInt("/createPatapataMob/tint/b"),
                config.getInt("/createPatapataMob/tint/a")
            ),
            config.getInt("/createPatapataMob/layer"),
            dropPowerup
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

        eventHandler.scheduleEvent("animate", 10, std::make_tuple(std::string("PataPata"), entityId));

        return entityId;
        } catch(const std::runtime_error& e) {
            std::cerr << "Error in createPatapaMob: " << e.what() << std::endl;
            exit(1);
        }
}

size_t EntityFactory::spawnBugMob(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  Utils::Vect2 pos, bool dropPowerup) {

    try {
        LoadConfig::ConfigData config = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createBugMob.json");

        size_t entityId = createBaseMob(
            container,
            config.getString("/createBugMob/spriteSheetPath"),
            config.getInt("/createBugMob/spriteSheetHeight"),
            config.getInt("/createBugMob/spriteSheetWidth"),
            config.getInt("/createBugMob/frames"),
            config.getBool("/createBugMob/twoDirections"),
            config.getBool("/createBugMob/reverse"),
            config.getString("/createBugMob/deathSpriteSheetPath"),
            config.getInt("/createBugMob/deathSpriteSheetHeight"),
            config.getInt("/createBugMob/deathSpriteSheetWidth"),
            config.getInt("/createBugMob/deathFrames"),
            pos,
            Utils::Vect2(
                config.getFloat("/createBugMob/velocity/x"),
                config.getFloat("/createBugMob/velocity/y")
            ),
            config.getInt("/createBugMob/maxHealth"),
            config.getInt("/createBugMob/damageValue"),
            config.getInt("/createBugMob/player"),
            config.getFloat("/createBugMob/scale"),
            config.getFloat("/createBugMob/rotation"),
            Utils::ColorR(
                config.getInt("/createBugMob/tint/r"),
                config.getInt("/createBugMob/tint/g"),
                config.getInt("/createBugMob/tint/b"),
                config.getInt("/createBugMob/tint/a")
            ),
            config.getInt("/createBugMob/layer"),
            dropPowerup
        );


        container.bindComponentToEntity(entityId, std::make_shared<Bug>());

        return entityId;
    } catch(const std::runtime_error& e) {
            std::cerr << "Error in createBugMob: " << e.what() << std::endl;
            exit(1);
        }
}
