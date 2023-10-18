//
// Created by Bartosz on 10/4/23.
//


#include "ParallaxPlanet.hpp"
#include "WindowInfoComponent.hpp"

ParallaxPlanet::ParallaxPlanet() : lastPlanetLayer(0),
          lastPlanetY(0),
          ticksSinceLastPlanet(0),
          nextTickThreshold(0)
    {
        PlanetsPath = {
            "assets/Planets/Planet_Furnace_01_560x560.png",
            "assets/Planets/Planet_Furnace_02_560x560.png",
            "assets/Planets/Planets_Desert_01_560x560.png",
            "assets/Planets/Planets_Desert_02_560x560.png",
            "assets/Planets/Planets_Grave_01_560x560.png",
            "assets/Planets/Planets_Grave_02_560x560.png",
            "assets/Planets/Planets_Ice_01_560x560.png",
            "assets/Planets/Planets_Ice_02_560x560.png",
            "assets/Planets/Planets_Jovian_01_560x560.png",
            "assets/Planets/Planets_Jovian_02_560x560.png",
            "assets/Planets/Planets_Jungle1_560x560.png",
            "assets/Planets/Planets_Jungle2_560x560.png",
            "assets/Planets/Planets_Ocean_01_560x560.png",
            "assets/Planets/Planets_Ocean_02_560x560.png",
            "assets/Planets/Planets_Rocky_01_560x560.png",
            "assets/Planets/Planets_Rocky_02_560x560.png",
            "assets/Planets/Planets_Shattered_01_560x560.png",
            "assets/Planets/Planets_Shattered_02_560x560.png",
            "assets/Planets/Planets_Tainted_01_560x560.png",
            "assets/Planets/Planets_Tainted_02_560x560.png",
            "assets/Planets/Planets_Vital_01_560x560.png",
            "assets/Planets/Planets_Vital_02_560x560.png"
        };
    }

ParallaxPlanet::ParallaxPlanet(const std::vector<std::string>& paths) : lastPlanetLayer(0),
          lastPlanetY(0),
          ticksSinceLastPlanet(0),
          nextTickThreshold(0),
          PlanetsPath(paths) {}

void ParallaxPlanet::update(GameEngine::ComponentsContainer &componentsContainer,
                                  GameEngine::EventHandler &eventHandler) {
    ticksSinceLastPlanet++;
    if (ticksSinceLastPlanet >= nextTickThreshold) {
        spawnPlanets(componentsContainer);
        ticksSinceLastPlanet = 0;
        nextTickThreshold = randomTickThreshold();
    }
}

int ParallaxPlanet::randomTickThreshold() {
    return rand() % (800) + 1000;
}

void ParallaxPlanet::spawnPlanets(GameEngine::ComponentsContainer &componentsContainer) {
    if (PlanetsPath.empty()) {
            PlanetsPath.swap(UsedPlanetsPath);
            UsedPlanetsPath.clear();
        }

        size_t randomIndex = rand() % PlanetsPath.size();
        std::string randomPath = PlanetsPath[randomIndex];
        PlanetsPath.erase(PlanetsPath.begin() + randomIndex);
        UsedPlanetsPath.push_back(randomPath);
        size_t randomLayer = lastPlanetLayer;
        while (randomLayer == lastPlanetLayer) {
            randomLayer = rand() % 3 + 2;
        }
        float scaleFactor = 0.3f * randomLayer;
        int random = rand() % (1080) - 200;
        float randomY = static_cast<float>(random);

        Utils::ColorR tint = {255, 255, 255, 255};
        float rotation = 0.0f;
        auto parallaxEntity = componentsContainer.createEntity();
        auto isParallaxComponent = std::make_shared<IsParallax>();
        componentsContainer.bindComponentToEntity(parallaxEntity, isParallaxComponent);
        auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(randomPath, Utils::Vect2{float(1920), randomY}, Utils::rect{0, 0, 560, 560}, randomLayer, scaleFactor, rotation, tint);
        componentsContainer.bindComponentToEntity(parallaxEntity, spriteComponent);
    };