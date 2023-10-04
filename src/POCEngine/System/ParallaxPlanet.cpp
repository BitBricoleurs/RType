//
// Created by Bartosz on 10/4/23.
//


#include "ParallaxPlanet.hpp"

ParallaxPlanetSystem::ParallaxPlanetSystem() : lastPlanetLayer(0),
          lastPlanetY(0),
          ticksSinceLastPlanet(0)
    {
        PlanetsPath = {
            "Planet_Furnace_01_560x560.png",
            "Planet_Furnace_02_560x560.png",
            "Planets_Desert_01_560x560.png",
            "Planets_Desert_02_560x560.png",
            "Planets_Grave_01_560x560.png",
            "Planets_Grave_02_560x560.png",
            "Planets_Ice_01_560x560.png",
            "Planets_Ice_02_560x560.png",
            "Planets_Jovian_01_560x560.png",
            "Planets_Jovian_02_560x560.png",
            "Planets_Jungle1_560x560.png",
            "Planets_Jungle2_560x560.png",
            "Planets_Ocean_01_560x560.png",
            "Planets_Ocean_02_560x560.png",
            "Planets_Rocky_01_560x560.png",
            "Planets_Rocky_02_560x560.png",
            "Planets_Shattered_01_560x560.png",
            "Planets_Shattered_02_560x560.png",
            "Planets_Tainted_01_560x560.png",
            "Planets_Tainted_02_560x560.png",
            "Planets_Vital_01_560x560.png",
            "Planets_Vital_02_560x560.png"
        };
    }


void ParallaxPlanetSystem::update(GameEngine::ComponentsContainer &componentsContainer,
                                  GameEngine::EventHandler &eventHandler) {
    ticksSinceLastPlanet++;
    if (ticksSinceLastPlanet >= nextTickThreshold) {
        spawnPlanets(componentsContainer);
        ticksSinceLastPlanet = 0;
        nextTickThreshold = randomTickThreshold();
    }
}

int ParallaxPlanetSystem::randomTickThreshold() {
    return rand() % (800) + 1000;
}

void ParallaxPlanetSystem::spawnPlanets(GameEngine::ComponentsContainer &componentsContainer) {
    if (PlanetsPath.empty()) {
            PlanetsPath.swap(UsedPlanetsPath);
            UsedPlanetsPath.clear();
        }

        size_t randomIndex = rand() % PlanetsPath.size();
        std::string randomPath = "assets/Planets/" + PlanetsPath[randomIndex];
        PlanetsPath.erase(PlanetsPath.begin() + randomIndex);
        UsedPlanetsPath.push_back(randomPath);
        size_t randomLayer = lastPlanetLayer;
        while (randomLayer == lastPlanetLayer) {
            randomLayer = rand() % 3 + 2;
        }
        float scaleFactor = 0.3f * randomLayer;
        int random = rand() % (1080) - 200;
        float randomY = static_cast<float>(random);

        GameEngine::ColorR tint = {255, 255, 255, 255};
        float rotation = 0.0f;
        auto parallaxEntity = componentsContainer.createEntity();
        auto isParallaxComponent = std::make_shared<IsParallaxComponent>();
        componentsContainer.bindComponentToEntity(parallaxEntity, isParallaxComponent);
        auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
            randomPath, GameEngine::Vect2{1920, randomY}, GameEngine::rect{0, 0, 560, 560}, randomLayer, scaleFactor, rotation, tint
        );
        componentsContainer.bindComponentToEntity(parallaxEntity, spriteComponent);
    };