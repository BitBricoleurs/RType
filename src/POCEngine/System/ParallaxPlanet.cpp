//
// Created by Bartosz on 10/4/23.
//


#include "ParallaxPlanet.hpp"
#include "WindowInfo.hpp"

ParallaxPlanet::ParallaxPlanet() : lastPlanetLayer(0),
          lastPlanetY(0),
          ticksSinceLastPlanet(0),
          nextTickThreshold(0)
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
    auto windows = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("WindowInfo"));
    size_t sizeWidth = 0;
    size_t sizeHeight = 0;

    for (const auto &window : windows) {
        auto windowOpt = componentsContainer.getComponent(window, GameEngine::ComponentsType::getComponentType("WindowInfo"));
        if (windowOpt.has_value()) {
            auto windowSize = std::dynamic_pointer_cast<WindowInfo>(windowOpt.value());
            sizeWidth = windowSize->windowWidth;
            sizeHeight = windowSize->windowHeight;
            break;
        }
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
        int random = rand() % (sizeHeight) - 200;
        float randomY = static_cast<float>(random);

        GameEngine::ColorR tint = {255, 255, 255, 255};
        float rotation = 0.0f;
        auto parallaxEntity = componentsContainer.createEntity();
        auto isParallaxComponent = std::make_shared<IsParallax>();
        componentsContainer.bindComponentToEntity(parallaxEntity, isParallaxComponent);
        auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(randomPath, GameEngine::Vect2{float(sizeWidth), randomY}, GameEngine::rect{0, 0, 560, 560}, randomLayer, scaleFactor, rotation, tint
        );
        componentsContainer.bindComponentToEntity(parallaxEntity, spriteComponent);
    };