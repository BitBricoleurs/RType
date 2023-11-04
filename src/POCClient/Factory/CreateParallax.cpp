/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Mob
*/

#include "EntityFactory.hpp"
#include <math.h>
#include <memory>
#include "ParallaxUtils.hpp"
#include <ostream>

namespace Client {

    size_t EntityFactory::CreateParallax(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler,
                                         const std::string &path, Utils::rect rect1, size_t layer, float scale, float rotation, Utils::ColorR tint, Utils::Vect2 pos, Utils::Vect2 velocity)
    {
        size_t entityId = container.createEntity();

        auto parallaxComponent = std::make_shared<IsParallax>();
        auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(path, pos, rect1, layer, scale, rotation, tint);
        auto velocityComponent = std::make_shared<PhysicsEngine::VelocityComponent>(velocity);
        auto positionComponent = std::make_shared<PhysicsEngine::PositionComponent2D>(pos);
        auto movementComponent = std::make_shared<PhysicsEngine::MovementComponent>();

        container.bindComponentToEntity(entityId, parallaxComponent);
        container.bindComponentToEntity(entityId, spriteComponent);
        container.bindComponentToEntity(entityId, velocityComponent);
        container.bindComponentToEntity(entityId, positionComponent);
        container.bindComponentToEntity(entityId, movementComponent);

        return entityId;
    }

    size_t EntityFactory::spawnParallax(GameEngine::ComponentsContainer & container, GameEngine::EventHandler & eventHandler, ParallaxType type, Utils::Vect2 pos, Utils::Vect2 velocity, float layer)
    {
        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createParallax.json");
            int parallaxSizeType = data.getSize("/types");
                for (int j = 0; j < parallaxSizeType; j++) {
                    if (static_cast<ParallaxType>(data.getInt("/types/" + std::to_string(j) + "/type")) == type) {
                        std::string path = data.getString("/types/" + std::to_string(j) + "/path");
                        Utils::rect rect1 = Utils::rect(data.getInt("/types/" + std::to_string(j) + "/rect/x"),
                                                        data.getInt("/types/" + std::to_string(j) + "/rect/y"),
                                                        data.getInt("/types/" + std::to_string(j) + "/rect/width"),
                                                        data.getInt("/types/" + std::to_string(j) + "/rect/height"));
                        float scale = data.getFloat("/types/" + std::to_string(j) + "/scale");
                        float rotation = data.getFloat("/types/" + std::to_string(j) + "/rotation");
                        Utils::ColorR tint = Utils::ColorR(data.getInt("/types/" + std::to_string(j) + "/tint/r"),
                                                            data.getInt("/types/" + std::to_string(j) + "/tint/g"),
                                                            data.getInt("/types/" + std::to_string(j) + "/tint/b"),
                                                            data.getInt("/types/" + std::to_string(j) + "/tint/a"));
                        return CreateParallax(container, eventHandler, path, rect1, layer, scale, rotation, tint, pos, velocity);
                    }
                }
                return 0;
        } catch (std::exception &e) {
            std::cerr << "Error loading parallax: " << e.what() << std::endl;
            exit(1);
        }
    }
}
