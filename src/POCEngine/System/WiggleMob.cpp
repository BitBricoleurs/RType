/*
** EPITECH PROJECT, 2023
** RType
** File description:
** WiggleMob
*/

#include "WiggleMob.hpp"

void WiggleMob::update(GameEngine::ComponentsContainer &componentsContainer,
                       GameEngine::EventHandler &eventHandler) {
  auto patapatas = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType("HeightVariation"));

  if (patapatas.empty()) {
    return;
  }

  for (auto &pata : patapatas) {
    auto heightVarOpt = componentsContainer.getComponent(
        pata, GameEngine::ComponentsType::getComponentType("HeightVariation"));

    auto positionOpt = componentsContainer.getComponent(
        pata,
        GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

    auto position = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(
        positionOpt.value());

    if (heightVarOpt.has_value()) {
      auto heightVar =
          std::dynamic_pointer_cast<HeightVariation>(heightVarOpt.value());
      if (position->pos.y < heightVar->baseY - heightVar->maxVar)
        heightVar->isGoingUp = true;
      else if (position->pos.y > heightVar->baseY + heightVar->maxVar)
        heightVar->isGoingUp = false;
      if (heightVar->isGoingUp)
        position->pos.y += heightVar->heightVarience;
      else
        position->pos.y -= heightVar->heightVarience;
    }
  }
}
