//
// Created by alexandre on 24/10/23.
//

#include "EntityFactory.hpp"

size_t Client::EntityFactory::spawnForcePod(GameEngine::ComponentsContainer &container, Utils::Vect2 pos, Utils::Vect2 vel, GameEngine::EventHandler &eventHandler)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createForcePod.json");

        size_t entityId = createBaseEntity(
                container,
                data.getString("/path"),
                data.getInt("/rect/height"),
                data.getInt("/rect/width"),
                data.getInt("/frames"),
                data.getBool("/twoDirections"),
                data.getBool("/reverse"),
                pos,
                vel,
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
        eventHandler.scheduleEvent("animate", data.getInt("/animateSpeed"), std::make_tuple(std::string("ForcePod"), entityId));
        std::cout << "Forcepod: " << entityId << std::endl;
        return entityId;
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from SpawnPowerUp System " << e.what() << std::endl;
        exit(84);
    }
}
