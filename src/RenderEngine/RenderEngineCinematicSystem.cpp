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
#include "AnimationComponent.hpp"

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
            float inHowMuchTime = config.getFloat(basePath + "components/CinematicComponent/inHowMuchTime");
            float playDuration = config.getFloat(basePath + "components/CinematicComponent/playDuration");
            float endPosX = config.getFloat(basePath + "components/CinematicComponent/endPosition/x");
            float endPosY = config.getFloat(basePath + "components/CinematicComponent/endPosition/y");
            auto cinematicComponent = std::make_shared<RenderEngine::CinematicComponent>(
                playDuration,
                Utils::Vect2(endPosX, endPosY)
            );
            componentsContainer.bindComponentToEntity(newEntity, cinematicComponent);
        }
        if (config.keyExists(basePath + "components/AnimationComponent")) {
            size_t framesCount = config.getInt(basePath + "components/AnimationComponent/framesCount");
            std::vector<Utils::rect> frames;
            for (size_t j = 0; j < framesCount; ++j) {
                std::string frameBasePath = basePath + "components/AnimationComponent/frames/" + std::to_string(j) + "/";
                int rectX = config.getInt(frameBasePath + "x");
                int rectY = config.getInt(frameBasePath + "y");
                int rectWidth = config.getInt(frameBasePath + "width");
                int rectHeight = config.getInt(frameBasePath + "height");
                frames.emplace_back(rectX, rectY, rectWidth, rectHeight);
            }
            auto animationComponent = std::make_shared<RenderEngine::AnimationComponent>(frames);
            componentsContainer.bindComponentToEntity(newEntity, animationComponent);
        }
    }
    auto eventID = componentsContainer.createEntity();
    auto cinematicEventComponent = std::make_shared<RenderEngine::CinematicEventComponent>();
    if (config.keyExists("/cinematic/events")) {
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
}


    void RenderEngineCinematicSystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        try {
            if (clock == 0 && jsonPath == "" && !isPlaying) {
            auto [json, scene] = std::any_cast<std::pair<std::string , std::string>>(eventHandler.getTriggeredEvent().second);
            jsonPath = json;
            nextScene = scene;
                if (jsonPath != "") {
                    loadJSON(jsonPath, componentsContainer);
                    isPlaying = true;
                }
                eventHandler.scheduleEvent("Cinematic", 1);
            }
            playCinematic(componentsContainer, eventHandler);

            if (nextScene != "" && !isPlaying && !isPaused) {
                eventHandler.queueEvent("gameEngineChangeScene", nextScene);
                endCinematic();
                auto windowID = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("WindowInfoComponent"));
                auto windowOpt = componentsContainer.getComponent(windowID, GameEngine::ComponentsType::getComponentType("WindowInfoComponent"));
                if (!windowOpt.has_value())
                    return;
                auto windowcast = std::static_pointer_cast<WindowInfoComponent>(windowOpt.value());
                windowcast->camera.target.x = windowcast->windowWidth / 2;
                windowcast->camera.target.y = windowcast->windowHeight / 2;

                windowcast->camera.zoom = 1;
                windowcast->camera.offset.x = windowcast->windowHeight / 2;
                windowcast->camera.offset.y = windowcast->windowWidth / 2;
                windowcast->camera.rotation = 0;
            }
        } catch (const std::bad_any_cast&) {
            std::cerr << "Cast error in RenderEngineCinematicSystem::update" << std::endl;
        }
    }

   void RenderEngineCinematicSystem::playCinematic(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    if (!isPaused) {
        auto posType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
        auto cinetype = GameEngine::ComponentsType::getComponentType("CinematicComponent");
        auto entitiesWithComponents = componentsContainer.getEntitiesWithComponent(
            posType,
            cinetype
        );
        for (const auto& entity : entitiesWithComponents) {
            auto cinematicOpt = componentsContainer.getComponent(entity, cinetype);
            auto positionOpt = componentsContainer.getComponent(entity, posType);
            auto spriteOpt = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
            if (!cinematicOpt.has_value() || !positionOpt.has_value())
                continue;
            auto cinematicComponent = std::static_pointer_cast<CinematicComponent>(cinematicOpt.value());
            auto positionComponent = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionOpt.value());

            float elapsed = clock - cinematicComponent->inHowMuchTime;
            float completionRatio = elapsed / cinematicComponent->playDuration;

            if (cinematicComponent->inHowMuchTime <= clock) {
                Utils::Vect2 delta = cinematicComponent->endPosition - positionComponent->pos;
                positionComponent->pos += delta * completionRatio;
            }
            if (spriteOpt.has_value()) {
                auto spriteComponent = std::static_pointer_cast<SpriteComponent>(spriteOpt.value());
                spriteComponent->pos = positionComponent->pos;
            }
        }
    }
    auto cineTextComponent = GameEngine::ComponentsType::getComponentType("CinematicEventComponent");
    auto windoType = GameEngine::ComponentsType::getComponentType("WindowInfoComponent");

    auto eventsID = componentsContainer.getEntityWithUniqueComponent(cineTextComponent);

    auto eventOpt = componentsContainer.getComponent(eventsID, cineTextComponent);
    auto windowID = componentsContainer.getEntityWithUniqueComponent(windoType);

    auto windowOpt = componentsContainer.getComponent(windowID, windoType);
    if (!windowOpt.has_value())
        return;
    auto windowcast = std::static_pointer_cast<WindowInfoComponent>(windowOpt.value());

    if (eventOpt.has_value()) {
        auto eventComponent = std::static_pointer_cast<CinematicEventComponent>(eventOpt.value());
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
            clockNonPausable = 0;
            jsonPath = "";
            isPaused = false;
            nextScene = "";
            CinematicDuration = 0;
        }
    }
