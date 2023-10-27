//
// Created by Clément Lagasse on 25/10/2023.
//

#include "RenderEngine.hpp"
#include "MenuSelect.hpp"

void Client::MenuSelect::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
     auto spriteCompType = GameEngine::ComponentsType::getComponentType("SpriteComponent");


    // Unselecting every other menu
    auto menuComp = GameEngine::ComponentsType::getComponentType("MenuNavigation");

    auto entitiesMenu = componentsContainer.getEntitiesWithComponent(menuComp);


    for (auto ett: entitiesMenu) {
        auto spriteCompMay = componentsContainer.getComponent(ett, spriteCompType);
        if (spriteCompMay.has_value()) {
            auto comp = spriteCompMay.value();
            auto spriteComp = std::static_pointer_cast<RenderEngine::SpriteComponent>(comp);
            spriteComp->rect1.x = 0;
        }
    }

    // Selecting the selected One and removing other selected in case there is multiple selection wich will never happened but if it does that's ok :)
    auto selectedComp = GameEngine::ComponentsType::getComponentType("IsSelected");

    auto entities = componentsContainer.getEntitiesWithComponent(selectedComp);
    if (entities.empty())
        return;
    bool expectFirst = false;
    if (entities.size() > 1) {
        for (auto entity : entities) {
            if (!expectFirst) {
                expectFirst = true;
                continue;
            }
            componentsContainer.unbindComponentFromEntity(entity, selectedComp);
        }
    }
    float padding = 3.0;
    auto spriteCompMay = componentsContainer.getComponent(entities[0], spriteCompType);
    if (spriteCompMay.has_value()) {
        auto comp = spriteCompMay.value();
        auto sprite = std::static_pointer_cast<RenderEngine::SpriteComponent>(comp);
        sprite->rect1.x = sprite->rect1.w + padding;
    } else {
        std::cerr << "Error while selecting an Menu Component" << std::endl;
    }
}