//
// Created by Bartosz on 10/23/23.
//

#include "RenderEngineCinematicSystem.hpp"
#include "CinematicComponent.hpp"
#include "PositionComponent2D.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include <string>
#include "CinematicEventComponent.hpp"
#include "EventHandler.hpp"

namespace RenderEngine {

        void RenderEngineCinematicSystem::loadJSON(const std::string &path, GameEngine::ComponentsContainer &componentsContainer) {
    LoadConfig::ConfigData config = LoadConfig::LoadConfig::getInstance().loadConfig(path);

    int entitiesSize = config.getSize("/cinematic/entities");
    CinematicDuration = config.getFloat("/cinematic/duration/time");

    for (int i = 0; i < entitiesSize; i++) {
        std::string basePath = "/cinematic/entities/" + std::to_string(i) + "/";
        auto newEntity = componentsContainer.createEntity();

        if (config.keyExists(basePath + "components/PositionComponent2D")) {
            float x = config.getFloat(basePath + "components/PositionComponent2D/x");
            float y = config.getFloat(basePath + "components/PositionComponent2D/y");
            auto positionComponent = std::make_shared<PhysicsEngine::PositionComponent2D>(Utils::Vect2(x, y));
            componentsContainer.bindComponentToEntity(newEntity, positionComponent);
        }

        if (config.keyExists(basePath + "components/SpriteComponent")) {
            std::string imagePath = config.getString(basePath + "components/SpriteComponent/imagePath");
            float posX = config.getFloat(basePath + "components/SpriteComponent/pos/x");
            float posY = config.getFloat(basePath + "components/SpriteComponent/pos/y");
            int rectX = config.getInt(basePath + "components/SpriteComponent/rect/x");
            int rectY = config.getInt(basePath + "components/SpriteComponent/rect/y");
            int rectWidth = config.getInt(basePath + "components/SpriteComponent/rect/width");
            int rectHeight = config.getInt(basePath + "components/SpriteComponent/rect/height");
            size_t layer = config.getInt(basePath + "components/SpriteComponent/layer");
            float scale = config.getFloat(basePath + "components/SpriteComponent/scale");
            float rotation = config.getFloat(basePath + "components/SpriteComponent/rotation");
            int tintR = config.getInt(basePath + "components/SpriteComponent/tint/r");
            int tintG = config.getInt(basePath + "components/SpriteComponent/tint/g");
            int tintB = config.getInt(basePath + "components/SpriteComponent/tint/b");
            int tintA = config.getInt(basePath + "components/SpriteComponent/tint/a");

            auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
                imagePath,
                Utils::Vect2(posX, posY),
                Utils::rect(rectX, rectY, rectWidth, rectHeight),
                layer,
                scale,
                rotation,
                Utils::ColorR(tintR, tintG, tintB, tintA)
            );
            componentsContainer.bindComponentToEntity(newEntity, spriteComponent);
        }

        if (config.keyExists(basePath + "components/TextComponent")) {
            std::string text = config.getString(basePath + "components/TextComponent/text");
            float posX = config.getFloat(basePath + "components/TextComponent/pos/x");
            float posY = config.getFloat(basePath + "components/TextComponent/pos/y");
            int fontSize = config.getInt(basePath + "components/TextComponent/fontSize");
            size_t layer = config.getInt(basePath + "components/TextComponent/layer");
            int colorR = config.getInt(basePath + "components/TextComponent/color/r");
            int colorG = config.getInt(basePath + "components/TextComponent/color/g");
            int colorB = config.getInt(basePath + "components/TextComponent/color/b");
            int colorA = config.getInt(basePath + "components/TextComponent/color/a");

            auto textComponent = std::make_shared<RenderEngine::TextComponent>(
                text,
                Utils::Vect2(posX, posY),
                fontSize,
                layer,
                Utils::ColorR(colorR, colorG, colorB, colorA)
            );
            componentsContainer.bindComponentToEntity(newEntity, textComponent);
        }

        if (config.keyExists(basePath + "components/CinematicComponent")) {
            float playDuration = config.getFloat(basePath + "components/CinematicComponent/playDuration");
            float endPosX = config.getFloat(basePath + "components/CinematicComponent/endPosition/x");
            float endPosY = config.getFloat(basePath + "components/CinematicComponent/endPosition/y");
            playDuration = playDuration;
            auto cinematicComponent = std::make_shared<RenderEngine::CinematicComponent>(
                playDuration,
                Utils::Vect2(endPosX, endPosY)
            );
            componentsContainer.bindComponentToEntity(newEntity, cinematicComponent);
        }
    }
    auto eventID = componentsContainer.createEntity();
    auto cinematicEventComponent = std::make_shared<RenderEngine::CinematicEventComponent>();
    int eventsSize = config.getSize("/cinematic/events");
    for (int j = 0; j < eventsSize; j++) {
        std::string eventBasePath = "/cinematic/events/" + std::to_string(j) + "/";
        std::string eventTypeString = config.getString(eventBasePath + "type");
        RenderEngine::CinematicEventType eventType;

        if (eventTypeString == "MoveCamera") {
            float x = config.getFloat(eventBasePath + "data/targetPosition/x");
            float y = config.getFloat(eventBasePath + "data/targetPosition/y");
            float duration = config.getFloat(eventBasePath + "data/duration");
            float inHowMuchTime = config.getFloat(eventBasePath + "data/inHowMuchTime");

            auto data = std::make_unique<RenderEngine::MoveCameraData>();
            data->targetPosition = Utils::Vect2(x, y);
            data->duration = duration;
            data->inHowMuchTime = inHowMuchTime;

            cinematicEventComponent->addEvent(RenderEngine::CinematicEventType::MoveCamera, std::move(data));
        }

        else if (eventTypeString == "ZoomCamera") {
            float zoomLevel = config.getFloat(eventBasePath + "data/zoomLevel");
            float duration = config.getFloat(eventBasePath + "data/duration");
            float inHowMuchTime = config.getFloat(eventBasePath + "data/inHowMuchTime");

            auto data = std::make_unique<RenderEngine::ZoomCameraData>();
            data->zoomLevel = zoomLevel;
            data->duration = duration;
            data->inHowMuchTime = inHowMuchTime;

            cinematicEventComponent->addEvent(RenderEngine::CinematicEventType::ZoomCamera, std::move(data));
        }

        else if (eventTypeString == "PlaySound") {
            std::string soundPath = config.getString(eventBasePath + "data/soundPath");
            float inHowMuchTime = config.getFloat(eventBasePath + "data/inHowMuchTime");
            float forHowMuchTime = config.getFloat(eventBasePath + "data/forHowMuchTime");

            auto data = std::make_unique<RenderEngine::PlaySoundData>();
            data->soundPath = soundPath;
            data->inHowMuchTime = inHowMuchTime;
            data->forHowMuchTime = forHowMuchTime;

            cinematicEventComponent->addEvent(RenderEngine::CinematicEventType::PlaySound, std::move(data));
        }

        else if (eventTypeString == "Pause") {
            float inHowMuchTime = config.getFloat(eventBasePath + "data/inHowMuchTime");

            auto data = std::make_unique<RenderEngine::PauseData>();
            data->inHowMuchTime = inHowMuchTime;

            cinematicEventComponent->addEvent(RenderEngine::CinematicEventType::Pause, std::move(data));
        }

        else if (eventTypeString == "Resume") {
            float inHowMuchTime = config.getFloat(eventBasePath + "data/inHowMuchTime");

            auto data = std::make_unique<RenderEngine::ResumeData>();
            data->inHowMuchTime = inHowMuchTime;

            cinematicEventComponent->addEvent(RenderEngine::CinematicEventType::Resume, std::move(data));
        }
    }
    componentsContainer.bindComponentToEntity(eventID, cinematicEventComponent);
}


    void RenderEngineCinematicSystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        if (clock == 0) {
            auto [jsonPath, nextScene] = std::any_cast<std::pair<std::string , std::string>>(eventHandler.getTriggeredEvent().second);

            if (jsonPath != "") {
                loadJSON(jsonPath, componentsContainer);
                isPlaying = true;
            }
            eventHandler.scheduleEvent("Cinematic", 1);
        }
        playCinematic(componentsContainer, eventHandler);
        return;

        if (nextScene != "" && !isPlaying && !isPaused) {
            endCinematic();
        }
    }

   void RenderEngineCinematicSystem::playCinematic(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    if (!isPaused) {
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
    }
    auto eventsID = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("CinematicEventComponent"));
    auto eventComponent = std::dynamic_pointer_cast<CinematicEventComponent>(
            componentsContainer.getComponent(eventsID[0], GameEngine::ComponentsType::getNewComponentType("CinematicEventComponent")).value()
        );
    auto windowID = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("WindowInfoComponent"));
    auto windowcast = std::dynamic_pointer_cast<WindowInfoComponent>(
            componentsContainer.getComponent(windowID[0], GameEngine::ComponentsType::getNewComponentType("WindowInfoComponent")).value()
        );

    for (size_t i = 0; i < eventComponent->eventData.size(); ++i) {
        auto& event = eventComponent->eventData[i];
        CinematicEventType eventType = eventComponent->eventTypes[i];

        switch (eventType) {
            case CinematicEventType::MoveCamera: {
                auto specificEvent = dynamic_cast<MoveCameraData*>(event.get());
                if (specificEvent && clock >= specificEvent->inHowMuchTime && clock <= (specificEvent->inHowMuchTime + specificEvent->duration)) {
                    float progress = (clock - specificEvent->inHowMuchTime) / specificEvent->duration;
                    windowcast->camera.target.x = Lerp(windowcast->camera.target.x, specificEvent->targetPosition.x, progress);
                    windowcast->camera.target.y = Lerp(windowcast->camera.target.y, specificEvent->targetPosition.y, progress);
                    if (windowcast->camera.target.x == specificEvent->targetPosition.x && windowcast->camera.target.y == specificEvent->targetPosition.y) {
                        eventComponent->eventData.erase(eventComponent->eventData.begin() + i);
                    }
                }
                break;
            }

            case CinematicEventType::ZoomCamera: {
                auto specificEvent = dynamic_cast<ZoomCameraData*>(event.get());
                if (specificEvent && clock >= specificEvent->inHowMuchTime && clock <= (specificEvent->inHowMuchTime + specificEvent->duration)) {
                    float progress = (clock - specificEvent->inHowMuchTime) / specificEvent->duration;
                    windowcast->camera.zoom = Lerp(windowcast->camera.zoom, specificEvent->zoomLevel, progress);
                    if (windowcast->camera.zoom == specificEvent->zoomLevel) {
                        eventComponent->eventData.erase(eventComponent->eventData.begin() + i);
                    }
                }
                break;
            }
            case CinematicEventType::Pause: {
                auto specifcEvent = dynamic_cast<PauseData*>(event.get());
                if (specifcEvent) {
                    if (specifcEvent->inHowMuchTime <= clockNonPausable) {
                        isPaused = true;
                        eventComponent->eventData.erase(eventComponent->eventData.begin() + i);
                    }
                }
            }

            case CinematicEventType::Resume: {
                auto specifcEvent = dynamic_cast<ResumeData*>(event.get());
                if (specifcEvent) {
                    if (specifcEvent->inHowMuchTime <= clockNonPausable) {
                        isPaused = false;
                        eventComponent->eventData.erase(eventComponent->eventData.begin() + i);
                    }
                }
            }
            default:
                break;
        }
    }
    if (clock >= CinematicDuration) {
        isPlaying = false;
        eventHandler.unscheduleEvent("Cinematic");
        }
    if (!isPaused)
        clock += 1.0f / 60.0f;
    clockNonPausable += 1.0f / 60.0f;
}


    void RenderEngineCinematicSystem::endCinematic() {
            isPlaying = false;
            clock = 0;
            //change scene
        }
    }
