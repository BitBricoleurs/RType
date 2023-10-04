//
// Created by alexandre on 03/10/23.
//

#include "BossStage.hpp"

BossStage::BossStage(int stage) : stage(stage) {}

size_t BossStage::getComponentType()
{
    return GameEngine::ComponentsType::getNewComponentType("BossStage");
}
