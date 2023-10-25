//
// Created by Bartosz on 10/23/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <string>
#include "Vect2.hpp"
#include <memory>
#include <vector>

namespace RenderEngine {

    enum class CinematicEventType {
        MoveCamera,
        ZoomCamera,
        PlaySound,
        Pause,
        Resume,
    };

    struct CinematicEventData {
        virtual ~CinematicEventData() = default;
    };

    struct MoveCameraData : public CinematicEventData {
        Utils::Vect2 targetPosition;
        float duration;
        float inHowMuchTime;
    };

    struct ZoomCameraData : public CinematicEventData {
        float zoomLevel;
        float duration;
        float inHowMuchTime;
    };

    struct PlaySoundData : public CinematicEventData {
        std::string soundPath;
        float inHowMuchTime;
        float forHowMuchTime;
    };

    struct PauseData : public CinematicEventData {
        float inHowMuchTime;
    };

    struct ResumeData : public CinematicEventData {
        float inHowMuchTime;
    };


    class CinematicEventComponent : public GameEngine::AComponent {
    public:
        CinematicEventComponent() = default;

        void addEvent(CinematicEventType type, std::unique_ptr<CinematicEventData> data) {
            eventTypes.push_back(type);
            eventData.push_back(std::move(data));
        }

        ~CinematicEventComponent() override = default;

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("CinematicEventComponent");
        }

        std::vector<CinematicEventType> eventTypes;
        std::vector<std::unique_ptr<CinematicEventData>> eventData;
    };
}
