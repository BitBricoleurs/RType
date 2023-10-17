#include "EntityFactory.hpp"

size_t
EntityFactory::createPlayerBullet(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos, GameEngine::Vect2 velocity, size_t typeBullet) {
    try {
        ConfigData data = LoadConfig::getInstance().loadConfig("config/Entity/createBulletPlayer.json");

        std::string bulletKeyPath = "/createBullet/bulletTypes/type" + std::to_string(typeBullet);
        std::string rectKeyPath = bulletKeyPath + "/rect";

        int rectH = data.getInt(rectKeyPath + "/h");
        int rectW = data.getInt(rectKeyPath + "/w");
        std::string path = data.getString(bulletKeyPath + "/path");

        size_t entityId = createBullet(
            container,
            path,
            rectH,
            rectW,
            data.getInt("/createBullet/frames"),
            data.getBool("/createBullet/twoDirections"),
            data.getBool("/createBullet/reverse"),
            pos,
            velocity,
            data.getBool("/createBullet/isPlayerBullet"),
            data.getInt("/createBullet/playerA"),
            data.getFloat("/createBullet/scale"),
            data.getFloat("/createBullet/rotation"),
            GameEngine::ColorR(
                data.getInt("/createBullet/tint/r"),
                data.getInt("/createBullet/tint/g"),
                data.getInt("/createBullet/tint/b"),
                data.getInt("/createBullet/tint/a")
            ),
            data.getInt("/createBullet/layer")
        );

        return entityId;
    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createPlayerBullet: " << e.what() << std::endl;
        exit(1);
    }
}

size_t
EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos, GameEngine::Vect2 velocity) {
    try {
        ConfigData data = LoadConfig::getInstance().loadConfig("config/Entity/createBulletEnemy.json");

        size_t entityId = createBullet(
            container,
            data.getString("/createBullet/spriteSheetPath"),
            data.getInt("/createBullet/spriteSheetHeight"),
            data.getInt("/createBullet/spriteSheetWidth"),
            data.getInt("/createBullet/frames"),
            data.getBool("/createBullet/twoDirections"),
            data.getBool("/createBullet/reverse"),
            pos,
            velocity,
            data.getBool("/createBullet/isPlayerBullet"),
            data.getInt("/createBullet/playerA"),
            data.getFloat("/createBullet/scale"),
            data.getFloat("/createBullet/rotation"),
            GameEngine::ColorR(
                data.getInt("/createBullet/tint/r"),
                data.getInt("/createBullet/tint/g"),
                data.getInt("/createBullet/tint/b"),
                data.getInt("/createBullet/tint/a")
            ),
            data.getInt("/createBullet/layer")
        );

        eventHandler.scheduleEvent(
            "animate", 10, std::make_tuple(std::string("EnemyBullet"), entityId));

        return entityId;
    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createBaseEnemyBullet: " << e.what() << std::endl;
        exit(1);
    }
}
