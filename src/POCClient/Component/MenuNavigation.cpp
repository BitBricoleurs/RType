//
// Created by Clément Lagasse on 25/10/2023.
//

#include "ComponentContainer.hpp"
#include "MenuNavigation.hpp"

size_t Client::MenuNavigation::getComponentType()
{
    return GameEngine::ComponentsType::getNewComponentType("MenuNavigation");
}

void Client::MenuNavigationMethods::setMenuNavigation(size_t entityId, size_t entityIdToNavigate, std::string whereNavigate, GameEngine::ComponentsContainer &componentsContainer)
{
    auto menuNavType = GameEngine::ComponentsType::getComponentType("MenuNavigation");
    auto mayCompEntityId = componentsContainer.getComponent(entityId, menuNavType);

    if (!mayCompEntityId.has_value()) {
        std::cerr << "Error while trying to connect Menu " << std::endl;
        return;
    }

    auto mayCompToNav = componentsContainer.getComponent(entityIdToNavigate, menuNavType);
    if (!mayCompToNav.has_value()) {
        std::cerr << "Error while trying to connect Menu " << std::endl;
        return;
    }

    auto menuNavEntity = std::static_pointer_cast<Client::MenuNavigation>(mayCompEntityId.value());

    for (auto key: menuNavEntity->_mapNav) {
        if (key.first == whereNavigate) {
            menuNavEntity->_mapNav[whereNavigate] = entityIdToNavigate;
            return;
        }
    }
}
