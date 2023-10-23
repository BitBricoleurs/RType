//
// Created by Bartosz on 10/23/23.
//

#include "RenderEngineCinematicSystem.hpp"
#include "CinematicComponent.hpp"
#include "PositionComponent2D.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include "PositionComponent2D.hpp"

namespace RenderEngine {

        void RenderEngineCinematicSystem::loadJSON(const std::string &path, GameEngine::ComponentsContainer &componentsContainer) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return;
        }

        nlohmann::json j;
        file >> j;

        for (const auto &entityData : j["cinematic"]["entities"]) {
            auto newEntity = componentsContainer.createEntity();

            if (entityData["components"].contains("PositionComponent2D")) {
                auto positionData = entityData["components"]["PositionComponent2D"];
                auto positionComponent = std::make_shared<PhysicsEngine::PositionComponent2D>(
                    Utils::Vect2(positionData["x"].get<float>(), positionData["y"].get<float>())
                );
                componentsContainer.bindComponentToEntity(newEntity, positionComponent);
            }

            if (entityData["components"].contains("SpriteComponent")) {
                auto spriteData = entityData["components"]["SpriteComponent"];
                auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
                    spriteData["imagePath"].get<std::string>(),
                    Utils::Vect2(spriteData["pos"]["x"].get<float>(), spriteData["pos"]["y"].get<float>()),
                    Utils::rect(spriteData["rect"]["x"].get<int>(), spriteData["rect"]["y"].get<int>(), spriteData["rect"]["width"].get<int>(), spriteData["rect"]["height"].get<int>()),
                    spriteData["layer"].get<size_t>(),
                    spriteData["scale"].get<float>(),
                    spriteData["rotation"].get<float>(),
                    Utils::ColorR(spriteData["tint"]["r"].get<int>(), spriteData["tint"]["g"].get<int>(), spriteData["tint"]["b"].get<int>(), spriteData["tint"]["a"].get<int>())
                );
                componentsContainer.bindComponentToEntity(newEntity, spriteComponent);
            }

            if (entityData["components"].contains("TextComponent")) {
                auto textData = entityData["components"]["TextComponent"];
                auto textComponent = std::make_shared<RenderEngine::TextComponent>(
                    textData["text"].get<std::string>(),
                    Utils::Vect2(textData["pos"]["x"].get<float>(), textData["pos"]["y"].get<float>()),
                    textData["fontSize"].get<int>(),
                    textData["layer"].get<size_t>(),
                    Utils::ColorR(textData["color"]["r"].get<int>(), textData["color"]["g"].get<int>(), textData["color"]["b"].get<int>(), textData["color"]["a"].get<int>())
                );
                componentsContainer.bindComponentToEntity(newEntity, textComponent);
            }

            if (entityData["components"].contains("CinematicComponent")) {
                auto cinematicData = entityData["components"]["CinematicComponent"];
                auto cinematicComponent = std::make_shared<RenderEngine::CinematicComponent>(
                    cinematicData["playDuration"].get<float>(),
                    Utils::Vect2(cinematicData["endPosition"]["x"].get<float>(), cinematicData["endPosition"]["y"].get<float>())
                );
                componentsContainer.bindComponentToEntity(newEntity, cinematicComponent);
            }
        }
        }

        void RenderEngineCinematicSystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
            auto [jsonPath, nextScene] = std::any_cast<std::pair<std::string , std::string>>(eventHandler.getTriggeredEvent().second);

            if (jsonPath != "") {
                loadJSON(jsonPath, componentsContainer);
            }
            playCinematic(componentsContainer, eventHandler);

            if (nextScene != "") {
                endCinematic();
            }
        }

        void RenderEngineCinematicSystem::playCinematic(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto entitiesWithComponents = componentsContainer.getEntitiesWithComponent(
        GameEngine::ComponentsType::getNewComponentType("PositionComponent2D"),
        GameEngine::ComponentsType::getNewComponentType("CinematicComponent")
    );

    for (const auto& entity : entitiesWithComponents) {
        auto cinematicComponent = std::dynamic_pointer_cast<CinematicComponent>(
            componentsContainer.getComponent(entity, GameEngine::ComponentsType::getNewComponentType("CinematicComponent")).value()
        );
        auto positionComponent = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(
            componentsContainer.getComponent(entity, GameEngine::ComponentsType::getNewComponentType("PositionComponent2D")).value()
        );

        float completionRatio = clock / cinematicComponent->playDuration;

        if (completionRatio > 1.0f) {
            completionRatio = 1.0f;
        }

        Utils::Vect2 delta = cinematicComponent->endPosition - positionComponent->pos;

        positionComponent->pos += delta * completionRatio;

    }
    clock += (1.0f / 60.0f);
}


        void RenderEngineCinematicSystem::endCinematic() {
            isPlaying = false;
            clock = 0;
            //change scene
        }

}