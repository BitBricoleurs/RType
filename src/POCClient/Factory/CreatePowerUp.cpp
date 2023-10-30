//
// Created by alexandre on 24/10/23.
//

#include "EntityFactory.hpp"

size_t Client::EntityFactory::spawnPowerUp(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, Utils::Vect2 pos, Utils::Vect2 vel, PowerUpType type)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPowerUp.json");

        int size = data.getSize("/powers");
        for (int i = 0; i < size; i++) {
            PowerUpType typeTab = static_cast<PowerUpType>(data.getInt("/powers/" + std::to_string(i) + "/type"));
            if (typeTab == type) {
                size_t entityId = createBaseEntity(
                        container,
                        data.getString("/powers/" + std::to_string(i) + "/path"),
                        data.getInt("/powers/" + std::to_string(i) + "/rect/height"),
                        data.getInt("/powers/" + std::to_string(i) + "/rect/width"),
                        data.getInt("/powers/" + std::to_string(i) + "/frames"),
                        data.getBool("/powers/" + std::to_string(i) + "/twoDirections"),
                        data.getBool("/powers/" + std::to_string(i) + "/reverse"),
                        pos,
                        vel,
                        0,
                        data.getFloat("/powers/" + std::to_string(i) + "/scale"),
                        data.getFloat("/powers/" + std::to_string(i) + "/rotation"),
                        Utils::ColorR(
                                data.getInt("/powers/" + std::to_string(i) + "/tint/r"),
                                data.getInt("/powers/" + std::to_string(i) + "/tint/g"),
                                data.getInt("/powers/" + std::to_string(i) + "/tint/b"),
                                data.getInt("/powers/" + std::to_string(i) + "/tint/a")
                        ),
                        data.getInt("/powers/" + std::to_string(i) + "/layer")
                        );
                eventHandler.scheduleEvent("animate", data.getInt("/powers/" + std::to_string(i) + "/animateSpeed") , std::make_tuple(std::string("PowerUp"), entityId));
                return entityId;
            }
        }
        return 0;
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        exit(84);
    }
}

std::vector<size_t> Client::EntityFactory::spawnPowerUpDualShoot(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, PowerUpType type, Utils::Vect2 pos, Utils::Vect2 pos2)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPowerUp.json");

        int size = data.getSize("/powers");
        for (int i = 0; i < size; i++) {
            PowerUpType typeTab = static_cast<PowerUpType>(data.getInt("/powers/" + std::to_string(i) + "/type"));
            if (typeTab == type) {
                size_t entityId = createBaseEntity(
                        container,
                        data.getString("/powers/" + std::to_string(i) + "/shootRed/path"),
                        data.getInt("/powers/" + std::to_string(i) + "/shootRed/rect/height"),
                        data.getInt("/powers/" + std::to_string(i) + "/shootRed/rect/width"),
                        data.getInt("/powers/" + std::to_string(i) + "/shootRed/frames"),
                        data.getBool("/powers/" + std::to_string(i) + "/shootRed/twoDirections"),
                        data.getBool("/powers/" + std::to_string(i) + "/shootRed/reverse"),
                        pos,
                        Utils::Vect2(data.getFloat("/powers/" + std::to_string(i) + "/shootRed/velocity/x"), data.getFloat("/powers/" + std::to_string(i) + "/shootRed/velocity/y")),
                        0,
                        data.getFloat("/powers/" + std::to_string(i) + "/shootRed/scale"),
                        data.getFloat("/powers/" + std::to_string(i) + "/shootRed/rotation"),
                        Utils::ColorR(
                                data.getInt("/powers/" + std::to_string(i) + "/shootRed/tint/r"),
                                data.getInt("/powers/" + std::to_string(i) + "/shootRed/tint/g"),
                                data.getInt("/powers/" + std::to_string(i) + "/shootRed/tint/b"),
                                data.getInt("/powers/" + std::to_string(i) + "/shootRed/tint/a")
                        ),
                        data.getInt("/powers/" + std::to_string(i) + "/shootRed/layer")
                        );
                size_t entityId2 = createBaseEntity(
                        container,
                        data.getString("/powers/" + std::to_string(i) + "/shootBlue/path"),
                        data.getInt("/powers/" + std::to_string(i) + "/shootBlue/rect/height"),
                        data.getInt("/powers/" + std::to_string(i) + "/shootBlue/rect/width"),
                        data.getInt("/powers/" + std::to_string(i) + "/shootBlue/frames"),
                        data.getBool("/powers/" + std::to_string(i) + "/shootBlue/twoDirections"),
                        data.getBool("/powers/" + std::to_string(i) + "/shootBlue/reverse"),
                        pos2,
                        Utils::Vect2(data.getFloat("/powers/" + std::to_string(i) + "/shootBlue/velocity/x"), data.getFloat("/powers/" + std::to_string(i) + "/shootBlue/velocity/y")),
                        0,
                        data.getFloat("/powers/" + std::to_string(i) + "/shootBlue/scale"),
                        data.getFloat("/powers/" + std::to_string(i) + "/shootBlue/rotation"),
                        Utils::ColorR(
                                data.getInt("/powers/" + std::to_string(i) + "/shootBlue/tint/r"),
                                data.getInt("/powers/" + std::to_string(i) + "/shootBlue/tint/g"),
                                data.getInt("/powers/" + std::to_string(i) + "/shootBlue/tint/b"),
                                data.getInt("/powers/" + std::to_string(i) + "/shootBlue/tint/a")
                        ),
                        data.getInt("/powers/" + std::to_string(i) + "/shootBlue/layer")
                        );
                std::vector<size_t> ids = {entityId, entityId2};
                return ids;
            }
        }
        return {};
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        exit(84);
    }
}
