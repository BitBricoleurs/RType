//
// Created by alexandre on 06/10/23.
//

#include "WindowInfoComponent.hpp"
#include "InitParallax.hpp"

void InitParallax::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto windows = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("WindowInfoComponent"));

    for (const auto &window : windows) {
        auto windowOpt = componentsContainer.getComponent(window, GameEngine::ComponentsType::getComponentType("WindowInfoComponent"));
        if (windowOpt.has_value()) {
            auto windowSize = std::dynamic_pointer_cast<RenderEngine::WindowInfoComponent>(windowOpt.value());

            auto parallaxIds = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsParallax"));
            for (const auto &parallaxID : parallaxIds) {
                componentsContainer.deleteEntity(parallaxID);
            }

            auto parallaxEntity = componentsContainer.createEntity();
            auto parallaxEntity2 = componentsContainer.createEntity();

            Utils::rect rect2(0, 0, windowSize->windowWidth, windowSize->windowHeight);
            Utils::Vect2 pos2(0, 0);
            Utils::Vect2 pos3(windowSize->windowWidth, 0);

            Utils::ColorR tint = {255,255,255,255};
            float scale = 1.0f;
            float rotation = 0.0f;

            auto isParallaxComponent = std::make_shared<IsParallax>();
            componentsContainer.bindComponentToEntity(parallaxEntity, isParallaxComponent);
            auto velocityComponent = std::make_shared<PhysicsEngine::VelocityComponent>(Utils::Vect2(1.0f, 0.0f));
            componentsContainer.bindComponentToEntity(parallaxEntity, velocityComponent);
            auto spritecompoennt2 = std::make_shared<RenderEngine::SpriteComponent>("assets/background_1.png", pos2, rect2, 2, scale, rotation, tint);
            componentsContainer.bindComponentToEntity(parallaxEntity, spritecompoennt2);

            auto isParallaxComponent1 = std::make_shared<IsParallax>();
            componentsContainer.bindComponentToEntity(parallaxEntity2, isParallaxComponent1);
            auto spritecompoennt3 = std::make_shared<RenderEngine::SpriteComponent>("assets/background_1.png", pos3, rect2, 2, scale, rotation, tint);
            componentsContainer.bindComponentToEntity(parallaxEntity2, spritecompoennt3);
        }
    }
}
