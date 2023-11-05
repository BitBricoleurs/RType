/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreatePlayer
*/

#include "EntityFactory.hpp"
#include "IsForcePod.hpp"

namespace Server {

    size_t EntityFactory::spawnForcePod(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, Utils::Vect2 pos)
    {
        try {

            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createForcePod.json");
            int hitBoxHeight = data.getInt("/hitBoxHeight");
            int hitBoxWidth = data.getInt("/hitBoxWidth");
            float scale = data.getFloat("/scale");
            Utils::Vect2 velocity = Utils::Vect2(
                data.getFloat("/velocity/x"),
                data.getFloat("/velocity/y")
            );
            size_t entityId = createBaseEntity(
                container,
                hitBoxHeight,
                hitBoxWidth,
                pos,
                velocity,
                scale
            );
            container.bindComponentToEntity(entityId, std::make_shared<IsForcePod>());
            std::vector<size_t> ids = {entityId};
            std::vector<std::any> args = {};
            args.emplace_back(static_cast<int>(pos.x * 1000));
            args.emplace_back(static_cast<int>(pos.y * 1000));
            args.emplace_back(static_cast<int>(velocity.x) * 1000);
            args.emplace_back(static_cast<int>(velocity.y) * 1000);
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_FORCEPOD", ids, "INT", args);
            std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
            return entityId;
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in spawnForcePod: " << e.what() << std::endl;
            exit(1);
        }
    }

}