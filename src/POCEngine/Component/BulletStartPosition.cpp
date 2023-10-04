//
// Created by alexandre on 03/10/23.
//

#include "BulletStartPosition.hpp"

BulletStartPosition::BulletStartPosition(float startX, float startY) : startX(startX), startY(startY) {}

size_t BulletStartPosition::getComponentType()
{
    return GameEngine::ComponentsType::getNewComponentType("BulletStartPosition");
}