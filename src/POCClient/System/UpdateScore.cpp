//
// Created by Theophilus Homawoo on 05/10/2023.
//

#include "UpdateScore.hpp"

namespace Client {

void UpdateScore::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    int scoreToAdd = std::any_cast<int>(eventHandler.getTriggeredEvent().second);
    auto scoreType = GameEngine::ComponentsType::getComponentType("Score");
    auto scoreId = componentsContainer.getEntityWithUniqueComponent(scoreType);
    auto scoreOpt = componentsContainer.getComponent(scoreId, GameEngine::ComponentsType::getComponentType("Score"));
    auto textOpt = componentsContainer.getComponent(scoreId, GameEngine::ComponentsType::getComponentType("TextComponent"));
    if (scoreOpt.has_value() && textOpt.has_value()) {
        auto score = std::static_pointer_cast<Client::Score>(scoreOpt.value());
        auto text = std::static_pointer_cast<RenderEngine::TextComponent>(textOpt.value());
        score->_score += scoreToAdd;
        std::string scoreString = std::to_string(score->_score);
        std::string spacedScoreString;
        for(char c : scoreString) {
            spacedScoreString += c;
            spacedScoreString += " ";
        }
        spacedScoreString.pop_back();
        text->text = "S c o r e : " + spacedScoreString;
    }
}
}