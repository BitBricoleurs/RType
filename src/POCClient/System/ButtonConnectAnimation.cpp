//
// Created by Clément Lagasse on 25/10/2023.
//

#include "ButtonConnectAnimation.hpp"

void Client::ButtonConnectAnimationNormal::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto compTypeButtonConnect = GameEngine::ComponentsType::getComponentType("IsButtonConnect");
    auto buttonType = GameEngine::ComponentsType::getComponentType("ButtonComponent");

    std::vector<size_t > entities = componentsContainer.getEntitiesWithComponent(compTypeButtonConnect);

    if (entities.empty() || entities.size() > 1) {
        return;
    }
    auto mayComp = componentsContainer.getComponent(entities[0], buttonType);
    if (!mayComp.has_value()) {
        return;
    }
    auto buttonConnect = std::static_pointer_cast<RenderEngine::ButtonComponent>(mayComp.value());

    buttonConnect->rect1.x = 0;
}

void Client::ButtonConnectAnimationHover::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto compTypeButtonConnect = GameEngine::ComponentsType::getComponentType("IsButtonConnect");
    auto buttonType = GameEngine::ComponentsType::getComponentType("ButtonComponent");

    std::vector<size_t > entities = componentsContainer.getEntitiesWithComponent(compTypeButtonConnect);

    if (entities.empty() || entities.size() > 1) {
        return;
    }
    auto mayComp = componentsContainer.getComponent(entities[0], buttonType);
    if (!mayComp.has_value()) {
        return;
    }
    auto buttonConnect = std::static_pointer_cast<RenderEngine::ButtonComponent>(mayComp.value());

    buttonConnect->rect1.x = buttonConnect->rect1.w;
}