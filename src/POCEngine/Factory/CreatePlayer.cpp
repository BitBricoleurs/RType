/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreatePlayer
*/

#include "EntityFactory.hpp"
#include "GravitySystemComponent.hpp"
#include "GravityComponent.hpp"
#include "IsOnGroundComponent.hpp"

size_t EntityFactory::createNewPlayer(GameEngine::ComponentsContainer &container,
                                      GameEngine::EventHandler &eventHandler,
                                      Utils::Vect2 pos) {
    this->player++;

    try {
        LoadConfig::ConfigData config = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPlayer.json");

        size_t chargeAnimationID = createChargeAnimation(
            container,
            config.getString("/createChargeAnimation/spriteSheetPath"),
            config.getInt("/createChargeAnimation/spriteSheetHeight"),
            config.getInt("/createChargeAnimation/spriteSheetWidth"),
            config.getInt("/createChargeAnimation/frames"),
            Utils::Vect2(
                config.getFloat("/createChargeAnimation/pos/x"),
                config.getFloat("/createChargeAnimation/pos/y")
            ),
            Utils::Vect2(
                config.getFloat("/createChargeAnimation/velocity/x"),
                config.getFloat("/createChargeAnimation/velocity/y")
            ),
            config.getFloat("/createChargeAnimation/scale"),
            config.getFloat("/createChargeAnimation/rotation"),
            Utils::ColorR(
                config.getInt("/createChargeAnimation/tint/r"),
                config.getInt("/createChargeAnimation/tint/g"),
                config.getInt("/createChargeAnimation/tint/b"),
                config.getInt("/createChargeAnimation/tint/a")
            ),
            config.getBool("/createChargeAnimation/twoDirection"),
            config.getBool("/createChargeAnimation/reverse"),
            config.getInt("/createChargeAnimation/direction"),
            config.getInt("/createChargeAnimation/playerA"),
            config.getInt("/createChargeAnimation/layer")
        );

        size_t entityId = createPlayer(
            container,
            config.getString("/createPlayer/spriteSheetPath"),
            config.getInt("/createPlayer/spriteSheetHeight"),
            config.getInt("/createPlayer/spriteSheetWidth"),
            config.getInt("/createPlayer/frames"),
            config.getBool("/createPlayer/twoDirections"),
            config.getBool("/createPlayer/reverse"),
            pos,
            Utils::Vect2(
                config.getFloat("/createPlayer/velocity/x"),
                config.getFloat("/createPlayer/velocity/y")
            ),
            config.getInt("/createPlayer/maxHealth"),
            config.getInt("/createPlayer/damageValue"),
            config.getInt("/createPlayer/bulletStartX"),
            config.getInt("/createPlayer/bulletStartY"),
            config.getInt("/createPlayer/playerA"),
            config.getFloat("/createPlayer/scale"),
            chargeAnimationID,
            config.getFloat("/createPlayer/rotation"),
            Utils::ColorR(
                config.getInt("/createPlayer/tint/r"),
                config.getInt("/createPlayer/tint/g"),
                config.getInt("/createPlayer/tint/b"),
                config.getInt("/createPlayer/tint/a")
            ),
            config.getInt("/createPlayer/typeBullet"),
            config.getInt("/createPlayer/layer")
        );

        eventHandler.scheduleEvent("animatePlayer", 15, entityId);
        eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));

        auto shootSound = std::make_shared<AudioEngine::AudioComponent>("assets/music/Hit 2.wav");
        container.bindComponentToEntity(entityId, shootSound);

        auto IdCharge = std::make_tuple(entityId, 0);
        eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);

        return entityId;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error in createNewPlayer: " << e.what() << std::endl;
        exit(1);
    }
}
