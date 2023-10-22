//
// Created by Bartosz on 10/4/23.
//

#pragma once

#include "ISystem.hpp"
#include "IsParallax.hpp"
#include "ComponentsType.hpp"
#include "VelocityComponent.hpp"
#include "SpriteComponent.hpp"

namespace Client {

    class ParallaxPlanet : public GameEngine::ISystem {
    public:
        ParallaxPlanet();
        explicit ParallaxPlanet(const std::vector<std::string>& paths);
        ~ParallaxPlanet() = default;

        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;

    private:
        int nextTickThreshold;
        size_t lastPlanetLayer;
        int lastPlanetY;
        int ticksSinceLastPlanet;
        std::vector<std::string> PlanetsPath;
        std::vector<std::string> UsedPlanetsPath;

        int randomTickThreshold();
        void spawnPlanets(GameEngine::ComponentsContainer &componentsContainer);
    };

}
