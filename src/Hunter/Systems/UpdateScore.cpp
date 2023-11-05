/*
** EPITECH PROJECT, 2023
** RType
** File description:
** LoseSystem
*/

#include "UpdateScore.hpp"

void UpdateScore::update(GameEngine::ComponentsContainer &componentsContainer,
                         GameEngine::EventHandler &eventHandler) {
    int scoreToAdd = 0;

    try {
        scoreToAdd = std::any_cast<int>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
        return;
    };
  auto scoreId = componentsContainer.getEntityWithUniqueComponent(
      GameEngine::ComponentsType::getComponentType("Score"));

  auto scoreOpt = componentsContainer.getComponent(
      scoreId, GameEngine::ComponentsType::getComponentType("Score"));

  auto textOpt = componentsContainer.getComponent(
      scoreId, GameEngine::ComponentsType::getComponentType("TextComponent"));

  if (scoreOpt.has_value() && textOpt.has_value()) {
    auto score = std::dynamic_pointer_cast<Score>(scoreOpt.value());
    auto text =
        std::dynamic_pointer_cast<RenderEngine::TextComponent>(textOpt.value());
    score->_score += scoreToAdd;
    text->text = "Score: " + std::to_string(score->_score);
  }
}