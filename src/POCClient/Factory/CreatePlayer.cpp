/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreatePlayer
*/

#include "EntityFactory.hpp"

size_t
EntityFactory::createNewPlayer(GameEngine::ComponentsContainer &container,
                               GameEngine::EventHandler &eventHandler,
                               GameEngine::Vect2 pos, PlayerNumber playerNumber) {

try {
    nlohmann::json config = loadConfig("config/Entity/createPlayer.json");
    size_t chargeAnimationID = createChargeAnimation(
        container,
        config["createChargeAnimation"]["spriteSheetPath"].get<std::string>(),
        config["createChargeAnimation"]["spriteSheetHeight"].get<int>(),
        config["createChargeAnimation"]["spriteSheetWidth"].get<int>(),
        config["createChargeAnimation"]["frames"].get<int>(),
        GameEngine::Vect2(
            config["createChargeAnimation"]["pos"]["x"].get<float>(),
            config["createChargeAnimation"]["pos"]["y"].get<float>()),
        GameEngine::Vect2(
            config["createChargeAnimation"]["velocity"]["x"].get<float>(),
            config["createChargeAnimation"]["velocity"]["y"].get<float>()),
        config["createChargeAnimation"]["scale"].get<float>(),
        config["createChargeAnimation"]["rotation"].get<float>(),
        GameEngine::ColorR(
            config["createChargeAnimation"]["tint"]["r"].get<int>(),
            config["createChargeAnimation"]["tint"]["g"].get<int>(),
            config["createChargeAnimation"]["tint"]["b"].get<int>(),
            config["createChargeAnimation"]["tint"]["a"].get<int>()),
        config["createChargeAnimation"]["twoDirection"].get<bool>(),
        config["createChargeAnimation"]["reverse"].get<bool>(),
        config["createChargeAnimation"]["direction"].get<int>(),
        static_cast<int>(playerNumber) + 1,
        config["createChargeAnimation"]["layer"].get<int>());

    size_t entityId = createPlayer(
        container, config["createPlayer"]["spriteSheetPath"].get<std::string>(),
        config["createPlayer"]["spriteSheetHeight"].get<int>(),
        config["createPlayer"]["spriteSheetWidth"].get<int>(),
        config["createPlayer"]["frames"].get<int>(),
        config["createPlayer"]["twoDirections"].get<bool>(),
        config["createPlayer"]["reverse"].get<bool>(), pos,
        GameEngine::Vect2(config["createPlayer"]["velocity"]["x"].get<float>(),
                          config["createPlayer"]["velocity"]["y"].get<float>()),
        static_cast<int>(playerNumber) + 1,
        config["createPlayer"]["scale"].get<float>(), chargeAnimationID,
        config["createPlayer"]["rotation"].get<float>(),
        GameEngine::ColorR(config["createPlayer"]["tint"]["r"].get<int>(),
                           config["createPlayer"]["tint"]["g"].get<int>(),
                           config["createPlayer"]["tint"]["b"].get<int>(),
                           config["createPlayer"]["tint"]["a"].get<int>()),
        config["createPlayer"]["layer"].get<int>());
    eventHandler.scheduleEvent("animatePlayer", 15, entityId);
    eventHandler.scheduleEvent(
        "animate", 5,
        std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
    std::cout << "FRRRR" << std::endl;
    std::shared_ptr<GameEngine::AudioComponent> shootSound = std::make_shared<GameEngine::AudioComponent>("assets/music/Shoot.wav");
    container.bindComponentToEntity(entityId, shootSound);
    auto IdCharge = std::make_tuple(entityId, 0);
    eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);
    eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
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
                               GameEngine::Vect2 pos, PlayerNumber playerNumber) {

try {
    nlohmann::json config = loadConfig("config/Entity/createPlayer.json");

    size_t chargeAnimationID = createChargeAnimation(
        container,
        config["createChargeAnimation"]["spriteSheetPath"].get<std::string>(),
        config["createChargeAnimation"]["spriteSheetHeight"].get<int>(),
        config["createChargeAnimation"]["spriteSheetWidth"].get<int>(),
        config["createChargeAnimation"]["frames"].get<int>(),
        GameEngine::Vect2(
            config["createChargeAnimation"]["pos"]["x"].get<float>(),
            config["createChargeAnimation"]["pos"]["y"].get<float>()),
        GameEngine::Vect2(
            config["createChargeAnimation"]["velocity"]["x"].get<float>(),
            config["createChargeAnimation"]["velocity"]["y"].get<float>()),
        config["createChargeAnimation"]["scale"].get<float>(),
        config["createChargeAnimation"]["rotation"].get<float>(),
        GameEngine::ColorR(
            config["createChargeAnimation"]["tint"]["r"].get<int>(),
            config["createChargeAnimation"]["tint"]["g"].get<int>(),
            config["createChargeAnimation"]["tint"]["b"].get<int>(),
            config["createChargeAnimation"]["tint"]["a"].get<int>()),
        config["createChargeAnimation"]["twoDirection"].get<bool>(),
        config["createChargeAnimation"]["reverse"].get<bool>(),
        config["createChargeAnimation"]["direction"].get<int>(),
        static_cast<int>(playerNumber) + 1,
        config["createChargeAnimation"]["layer"].get<int>());

    size_t entityId = createSharhips(
        container, config["createPlayer"]["spriteSheetPath"].get<std::string>(),
        config["createPlayer"]["spriteSheetHeight"].get<int>(),
        config["createPlayer"]["spriteSheetWidth"].get<int>(),
        config["createPlayer"]["frames"].get<int>(),
        config["createPlayer"]["twoDirections"].get<bool>(),
        config["createPlayer"]["reverse"].get<bool>(), pos,
        GameEngine::Vect2(config["createPlayer"]["velocity"]["x"].get<float>(),
                          config["createPlayer"]["velocity"]["y"].get<float>()),
        static_cast<int>(playerNumber) + 1,
        config["createPlayer"]["scale"].get<float>(), chargeAnimationID,
        config["createPlayer"]["rotation"].get<float>(),
        GameEngine::ColorR(config["createPlayer"]["tint"]["r"].get<int>(),
                           config["createPlayer"]["tint"]["g"].get<int>(),
                           config["createPlayer"]["tint"]["b"].get<int>(),
                           config["createPlayer"]["tint"]["a"].get<int>()),
        config["createPlayer"]["layer"].get<int>());
    eventHandler.scheduleEvent("animatePlayer", 15, entityId);
    eventHandler.scheduleEvent(
        "animate", 5,
        std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
    std::shared_ptr<GameEngine::AudioComponent> shootSound =
        std::make_shared<GameEngine::AudioComponent>("assets/music/Shoot.wav");
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