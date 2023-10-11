//
// Created by alexandre on 06/10/23.
//

#include "ToggleFullScreen.hpp"

void GameEngine::ToggleFullScreen::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    int display = GetCurrentMonitor();
    SetWindowSize(300, 300);
    if (IsWindowFullscreen()) {
        SetWindowSize(0, 0);
    } else {
        SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    }
    ToggleFullscreen();
    auto windows = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("WindowInfo"));

    for (const auto &window : windows) {
        auto windowOpt = componentsContainer.getComponent(window, GameEngine::ComponentsType::getComponentType("WindowInfo"));
        if (windowOpt.has_value()) {
            auto windowSize = std::dynamic_pointer_cast<WindowInfoComponent>(windowOpt.value());
            std::cout << "New size:" << windowSize->windowWidth << ":" << windowSize->windowHeight << std::endl;
            windowSize->windowWidth = GetScreenWidth();
            windowSize->windowHeight = GetScreenHeight();
        }
    }

    eventHandler.queueEvent("InitParallax");
}
