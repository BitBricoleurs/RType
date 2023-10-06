//
// Created by alexandre on 06/10/23.
//

#include "ToggleFullScreen.hpp"

void GameEngine::ToggleFullScreen::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    SetWindowSize(1920,1080);
    ToggleFullscreen();
    auto windows = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("WindowInfo"));

    for (const auto &window : windows) {
        auto windowOpt = componentsContainer.getComponent(window, GameEngine::ComponentsType::getComponentType("WindowInfo"));
        if (windowOpt.has_value()) {
            auto windowSize = std::dynamic_pointer_cast<WindowInfoComponent>(windowOpt.value());
            windowSize->windowWidth = GetScreenWidth();
            windowSize->windowHeight = GetScreenHeight();
        }
    }

    eventHandler.queueEvent("InitParallax");
}
