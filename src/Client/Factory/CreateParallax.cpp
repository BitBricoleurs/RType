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
                                         const std::string &path, Utils::rect rect1, size_t layer, float scale, float rotation, Utils::ColorR tint, Utils::Vect2 pos, Utils::Vect2 velocity, int frames, bool twoDirections, bool reverse)
    {
        size_t entityId = container.createEntity();

        auto parallaxComponent = std::make_shared<IsParallax>();
        auto velocityComponent = std::make_shared<PhysicsEngine::VelocityComponent>(velocity);
        auto positionComponent = std::make_shared<PhysicsEngine::PositionComponent2D>(pos);
        auto movementComponent = std::make_shared<PhysicsEngine::MovementComponent>();


        container.bindComponentToEntity(entityId, parallaxComponent);
        container.bindComponentToEntity(entityId, velocityComponent);
        container.bindComponentToEntity(entityId, positionComponent);
        container.bindComponentToEntity(entityId, movementComponent);

        if (frames > 1) {
            auto spriteAnimationComponent = initAnimation(path, frames, rect1.w, rect1.h, twoDirections, reverse, velocity.x, 0);

            Utils::rect spriteRect = {0, 0, 0, 0};

            spriteRect.w = spriteAnimationComponent->frameWidth;
            spriteRect.h = spriteAnimationComponent->frameHeight;
            spriteRect.x = spriteAnimationComponent->currentFrame.x;
            spriteRect.y = spriteAnimationComponent->currentFrame.y;
            auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(path, pos, spriteRect, static_cast<size_t>(layer), scale, rotation, tint);
            container.bindComponentToEntity(entityId, spriteComponent);
            container.bindComponentToEntity(entityId, spriteAnimationComponent);
            eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("SpriteAnime"), entityId));
        } else {
            auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(path, pos, rect1, layer, scale, rotation, tint);
            container.bindComponentToEntity(entityId, spriteComponent);
        }

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
                        int frames = data.getInt("/types/" + std::to_string(j) + "/frames");
                        bool twoDirections = data.getBool("/types/" + std::to_string(j) + "/twoDirections");
                        bool reverse = data.getBool("/types/" + std::to_string(j) + "/reverse");
                        return CreateParallax(container, eventHandler, path, rect1, layer, scale, rotation, tint, pos, velocity, frames, twoDirections, reverse);
                    }
                }
                return 0;
        } catch (std::exception &e) {
            std::cerr << "Error loading parallax: " << e.what() << std::endl;
            exit(1);
        }
    }
}
