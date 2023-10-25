//
// Created by alexandre on 24/10/23.
//

#include "EntityFactory.hpp"

size_t Client::EntityFactory::spawnForcePod(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createForcePod.json");

        Utils::Vect2 pos = {0, 0};
        Utils::Vect2 velocity = {0, 0};
        size_t entityId = createBaseEntity(
                container,
                data.getString("/path"),
                data.getInt("/rect/height"),
                data.getInt("/rect/width"),
                data.getInt("/frames"),
                data.getBool("/twoDirections"),
                data.getBool("/reverse"),
                pos,
                velocity,
                0,
                data.getFloat("/scale"),
                data.getFloat("/rotation"),
                Utils::ColorR(
                        data.getInt("/tint/r"),
                        data.getInt("/tint/g"),
                        data.getInt("/tint/b"),
                        data.getInt("/tint/a")
                ),
                data.getInt("/layer")
                );
        eventHandler.scheduleEvent("animate", 15, std::make_tuple(std::string("ForcePod"), entityId));
        return entityId;
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from SpawnPowerUp System " << e.what() << std::endl;
        exit(84);
    }
}