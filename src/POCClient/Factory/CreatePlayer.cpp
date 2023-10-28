/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreatePlayer
*/

#include "EntityFactory.hpp"

namespace Client {

    size_t EntityFactory::createNewPlayer(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, Utils::Vect2 pos, PlayerNumber playerNumber) {

    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPlayer.json");
        size_t chargeAnimationID = createChargeAnimation(
            container,
            data.getString("/createChargeAnimation/spriteSheetPath"),
            data.getInt("/createChargeAnimation/spriteSheetHeight"),
            data.getInt("/createChargeAnimation/spriteSheetWidth"),
            data.getInt("/createChargeAnimation/frames"),
            Utils::Vect2(
                data.getFloat("/createChargeAnimation/pos/x"),
                data.getFloat("/createChargeAnimation/pos/y")),
            Utils::Vect2(
                data.getFloat("/createChargeAnimation/velocity/x"),
                data.getFloat("/createChargeAnimation/velocity/y")),
            data.getFloat("/createChargeAnimation/scale"),
            data.getFloat("/createChargeAnimation/rotation"),
            Utils::ColorR(
                data.getInt("/createChargeAnimation/tint/r"),
                data.getInt("/createChargeAnimation/tint/g"),
                data.getInt("/createChargeAnimation/tint/b"),
                data.getInt("/createChargeAnimation/tint/a")),
            data.getBool("/createChargeAnimation/twoDirection"),
            data.getBool("/createChargeAnimation/reverse"),
            data.getInt("/createChargeAnimation/direction"),
            static_cast<int>(playerNumber) + 1,
            data.getInt("/createChargeAnimation/layer"));

        size_t entityId = createPlayer(
            container,
            data.getString("/createPlayer/spriteSheetPath"),
            data.getInt("/createPlayer/spriteSheetHeight"),
            data.getInt("/createPlayer/spriteSheetWidth"),
            data.getInt("/createPlayer/frames"),
            data.getBool("/createPlayer/twoDirections"),
            data.getBool("/createPlayer/reverse"),
            pos,
            Utils::Vect2(
                data.getFloat("/createPlayer/velocity/x"),
                data.getFloat("/createPlayer/velocity/y")),
            static_cast<int>(playerNumber) + 1,
            data.getFloat("/createPlayer/scale"), chargeAnimationID,
            data.getFloat("/createPlayer/rotation"),
            Utils::ColorR(
                data.getInt("/createPlayer/tint/r"),
                data.getInt("/createPlayer/tint/g"),
                data.getInt("/createPlayer/tint/b"),
                data.getInt("/createPlayer/tint/a")),
            data.getInt("/createPlayer/layer"));
        eventHandler.scheduleEvent("animatePlayer", 15, entityId);
        eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
        
        std::shared_ptr<AudioEngine::AudioComponent> shootSound = std::make_shared<AudioEngine::AudioComponent>(data.getString("/createPlayer/pathSound"));
        container.bindComponentToEntity(entityId, shootSound);
        auto IdCharge = std::make_tuple(entityId, 0);
        eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);
        registerPlayer(entityId, playerNumber);
        return entityId;
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON error in createPlayer: " << e.what() << std::endl;
        exit(1);
    }
    }

    size_t
    EntityFactory::createNewStarship(GameEngine::ComponentsContainer &container,
                                   GameEngine::EventHandler &eventHandler,
                                   Utils::Vect2 pos, PlayerNumber playerNumber) {

    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPlayer.json");

        size_t chargeAnimationID = createChargeAnimation(
            container,
            data.getString("/createChargeAnimation/spriteSheetPath"),
            data.getInt("/createChargeAnimation/spriteSheetHeight"),
            data.getInt("/createChargeAnimation/spriteSheetWidth"),
            data.getInt("/createChargeAnimation/frames"),
            Utils::Vect2(
                data.getFloat("/createChargeAnimation/pos/x"),
                data.getFloat("/createChargeAnimation/pos/y")),
            Utils::Vect2(
                data.getFloat("/createChargeAnimation/velocity/x"),
                data.getFloat("/createChargeAnimation/velocity/y")),
            data.getFloat("/createChargeAnimation/scale"),
            data.getFloat("/createChargeAnimation/rotation"),
            Utils::ColorR(
                data.getInt("/createChargeAnimation/tint/r"),
                data.getInt("/createChargeAnimation/tint/g"),
                data.getInt("/createChargeAnimation/tint/b"),
                data.getInt("/createChargeAnimation/tint/a")),
            data.getBool("/createChargeAnimation/twoDirection"),
            data.getBool("/createChargeAnimation/reverse"),
            data.getInt("/createChargeAnimation/direction"),
            static_cast<int>(playerNumber) + 1,
            data.getInt("/createChargeAnimation/layer"));

        size_t entityId = createSharhips(
            container,
            data.getString("/createPlayer/spriteSheetPath"),
            data.getInt("/createPlayer/spriteSheetHeight"),
            data.getInt("/createPlayer/spriteSheetWidth"),
            data.getInt("/createPlayer/frames"),
            data.getBool("/createPlayer/twoDirections"),
            data.getBool("/createPlayer/reverse"),
            pos,
            Utils::Vect2(
                data.getFloat("/createPlayer/velocity/x"),
                data.getFloat("/createPlayer/velocity/y")),
            static_cast<int>(playerNumber) + 1,
            data.getFloat("/createPlayer/scale"), chargeAnimationID,
            data.getFloat("/createPlayer/rotation"),
            Utils::ColorR(
                data.getInt("/createPlayer/tint/r"),
                data.getInt("/createPlayer/tint/g"),
                data.getInt("/createPlayer/tint/b"),
                data.getInt("/createPlayer/tint/a")),
            data.getInt("/createPlayer/layer"));

        eventHandler.scheduleEvent("animatePlayer", 15, entityId);
        eventHandler.scheduleEvent(
            "animate", 5,
            std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
        std::shared_ptr<AudioEngine::AudioComponent> shootSound =
            std::make_shared<AudioEngine::AudioComponent>("assets/music/Shoot.wav");
        container.bindComponentToEntity(entityId, shootSound);
        auto IdCharge = std::make_tuple(entityId, 0);
        eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);
        eventHandler.scheduleEvent(
            "animate", 5,
            std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
        registerPlayer(entityId, playerNumber);
        return entityId;
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON error in createPlayer: " << e.what() << std::endl;
        exit(1);
    }
    }

}