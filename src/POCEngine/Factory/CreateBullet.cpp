/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateNewBullet
*/

#include "EntityFactory.hpp"

size_t EntityFactory::createPlayerBullet(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, GameEngine::Vect2 pos, GameEngine::Vect2 velocity, const std::string &path, GameEngine::rect rect1, size_t type) {
    size_t entityId;

    try {
        ConfigData config = LoadConfig::getInstance().loadConfig("config/Entity/createBulletPlayer.json");

        if (type == 1) {
            entityId = createBullet(
                container,
                path,
                rect1.h,
                rect1.w,
                config.getInt("/createBullet/frames"),
                config.getBool("/createBullet/twoDirections"),
                config.getBool("/createBullet/reverse"),
                pos,
                velocity,
                config.getInt("/createBullet/damageValue"),
                config.getBool("/createBullet/isPlayerBullet"),
                config.getInt("/createBullet/playerA"),
                config.getString("/createBullet/pathSound"),
                config.getFloat("/createBullet/scale"),
                config.getFloat("/createBullet/rotation"),
                GameEngine::ColorR(
                    config.getInt("/createBullet/tint/r"),
                    config.getInt("/createBullet/tint/g"),
                    config.getInt("/createBullet/tint/b"),
                    config.getInt("/createBullet/tint/a")
                ),
                config.getInt("/createBullet/layer")
            );
        } else if (type == 2) {
            entityId = createBullet(container, path, 32, 512, 8, false, false, pos, velocity, 100, true, 0, "assets/music/Shoot 2.wav", 1.0f, 0.0f, GameEngine::ColorR(255, 255, 255, 255), 7);
            auto isBulletopt = container.getComponent(entityId, GameEngine::ComponentsType::getComponentType("IsBullet"));
            auto bulletcast = std::dynamic_pointer_cast<IsBullet>(*isBulletopt);
            bulletcast->passingThrough = true;
            eventHandler.scheduleEvent(
            "animate", 20, std::make_tuple(std::string("PlayerBullet"), entityId));
        }
    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createPlayerBullet: " << e.what() << std::endl;
        exit(1);
    }

    return entityId;
}

size_t EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, GameEngine::Vect2 pos, GameEngine::Vect2 velocity) {
    try {
        ConfigData config = LoadConfig::getInstance().loadConfig("config/Entity/createBulletEnemy.json");

        size_t entityId = createBullet(
            container,
            config.getString("/createBullet/spriteSheetPath"),
            config.getInt("/createBullet/spriteSheetHeight"),
            config.getInt("/createBullet/spriteSheetWidth"),
            config.getInt("/createBullet/frames"),
            config.getBool("/createBullet/twoDirections"),
            config.getBool("/createBullet/reverse"),
            pos,
            velocity,
            config.getInt("/createBullet/damageValue"),
            config.getBool("/createBullet/isPlayerBullet"),
            config.getInt("/createBullet/playerA"),
            config.getString("/createBullet/pathSound"),
            config.getFloat("/createBullet/scale"),
            config.getFloat("/createBullet/rotation"),
            GameEngine::ColorR(
                config.getInt("/createBullet/tint/r"),
                config.getInt("/createBullet/tint/g"),
                config.getInt("/createBullet/tint/b"),
                config.getInt("/createBullet/tint/a")
            ),
            config.getInt("/createBullet/layer")
        );

        eventHandler.scheduleEvent("animate", 10, std::make_tuple(std::string("EnemyBullet"), entityId));

        return entityId;
    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createBaseEnemyBullet: " << e.what() << std::endl;
        exit(1);
    }
}
