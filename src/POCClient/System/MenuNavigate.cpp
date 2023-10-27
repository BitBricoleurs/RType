//
// Created by Clément Lagasse on 25/10/2023.
//

#include <unordered_map>
#include "ComponentsType.hpp"
#include "MenuNavigate.hpp"
#include "MenuNavigation.hpp"

std::unordered_map<std::string, std::string> MAP_EVENT_DIRECTION =
        {
        {"UP_KEY_PRESSED", "UP"},
        {"DOWN_KEY_PRESSED", "DOWN"},
        {"LEFT_KEY_PRESSED", "LEFT"},
        {"RIGHT_KEY_PRESSED", "RIGHT"}
        };

void Client::MenuNavigate::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto event = eventHandler.getTriggeredEvent();
    std::string direction = "";

    for (auto key: MAP_EVENT_DIRECTION) {
        if (key.first == event.first) {
            direction = key.second;
            break;
        }
    }
    if (direction == "") {
        std::cerr << "The direction is not found check MenuNavigate.cpp" << std::endl;
        return;
    }
    auto selectType = GameEngine::ComponentsType::getComponentType("IsSelected");

    auto entities = componentsContainer.getEntitiesWithComponent(selectType);
    if (entities.empty())
        return;
    if (entities.size() > 1) {
        eventHandler.queueEvent("UPDATE_SELECT");
        eventHandler.queueEvent(event.first, event.second);
        return;
    }
    auto menuNavigatorType = GameEngine::ComponentsType::getComponentType("MenuNavigation");
    auto menuMayComp = componentsContainer.getComponent(entities[0], menuNavigatorType);
    if (!menuMayComp.has_value()){
        std::cerr << "The Menu selected does not have MenuNavigation check MenuNavigation.cpp" << std::endl;
        return;
    }
    auto comp = menuMayComp.value();
    auto menuComp = std::static_pointer_cast<Client::MenuNavigation>(comp);
    size_t newSelected = menuComp->_mapNav[direction];

    auto mayMenuNew = componentsContainer.getComponent(newSelected, menuNavigatorType);
    if (!mayMenuNew.has_value()) {
        std::cerr << "Tried to select an Entitty that does not have MenuNavigation Comp check MenuNavigation.cpp";
        return;
    }
    auto selectComp = std::make_shared<Client::IsSelected>();
    componentsContainer.unbindComponentFromEntity(entities[0], selectType);
    componentsContainer.bindComponentToEntity(newSelected, selectComp);
    eventHandler.queueEvent("UPDATE_SELECT");
}