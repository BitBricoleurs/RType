//
// Created by clagasse on 11/1/23.
//

#include "BulletComponent.hpp"

size_t Server::BulletTypeComp::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("BulletType");
}

size_t Server::BulletOwnerComp::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("BulletOwner");
}