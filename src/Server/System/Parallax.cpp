//
// Created by alexandre on 03/10/23.
//

#include "Parallax.hpp"

namespace Server {

    void Parallax::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        auto parallaxEntities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsParallax"));
        std::sort(parallaxEntities.begin(), parallaxEntities.end());

        for (auto entityID : parallaxEntities) {
            auto components = componentsContainer.getComponentsFromEntity(entityID);

            for (const auto &componentOpt : components) {
                auto parallaxOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getNewComponentType("IsParallax"));
                auto posOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getNewComponentType("PositionComponent2D"));

                if (parallaxOpt.has_value() && posOpt.has_value()) {
                    auto parallax = std::static_pointer_cast<IsParallax>(parallaxOpt.value());
                    auto pos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posOpt.value());
                    if (pos->pos.x <= -1920 && parallax->isLooping) {
                        pos->pos.x = pos->pos.x * -1;
                        EntityFactory::getInstance().updateEntityNetworkWithPos(eventHandler, entityID, pos->pos);
                    }
                }
            }
        }
    }
}
