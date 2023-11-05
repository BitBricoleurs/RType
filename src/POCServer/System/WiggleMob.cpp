/*
** EPITECH PROJECT, 2023
** RType
** File description:
** WiggleMob
*/

#include "WiggleMob.hpp"

void Server::WiggleMob::update(GameEngine::ComponentsContainer &componentsContainer,
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
    auto velocityOpt = componentsContainer.getComponent(
        pata, GameEngine::ComponentsType::getComponentType("VelocityComponent"));

    if (!positionOpt.has_value() || !velocityOpt.has_value() ||
        !heightVarOpt.has_value())
      continue;
    auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(
        positionOpt.value());
    auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(
        velocityOpt.value());
    auto heightVar =
        std::static_pointer_cast<Server::HeightVariation>(heightVarOpt.value());

    if (heightVar->isGoingUp && position->pos.y > heightVar->baseY + heightVar->maxVar)
        heightVar->isGoingUp = false;
    else if (!heightVar->isGoingUp && position->pos.y < heightVar->baseY - heightVar->maxVar)
        heightVar->isGoingUp = true;
    else
      continue;
  
    velocity->velocity.y = velocity->velocity.y * -1;
    auto &factory = EntityFactory::getInstance();
    factory.updateEntityNetworkWithVelocity(eventHandler, pata, velocity->velocity);
  }
}
