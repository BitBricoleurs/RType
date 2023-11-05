//
// Created by Theophilus Homawoo on 05/10/2023.
//

#include "UpdateScore.hpp"

namespace Client {

void UpdateScore::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {

    try {

    std::shared_ptr<Network::OwnedMessage> message;
    message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
       
    std::shared_ptr<Network::IMessage> IMessage = message->message;
    std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

    std::vector<std::any> args = messageData->getArgs();

    int score = std::any_cast<int>(args[0]);
    auto scoreType = GameEngine::ComponentsType::getComponentType("Score");
    auto scoreId = componentsContainer.getEntityWithUniqueComponent(scoreType);
    auto scoreOpt = componentsContainer.getComponent(scoreId, GameEngine::ComponentsType::getComponentType("Score"));
    auto textOpt = componentsContainer.getComponent(scoreId, GameEngine::ComponentsType::getComponentType("TextComponent"));
    if (scoreOpt.has_value() && textOpt.has_value()) {
        auto scoreComp = std::static_pointer_cast<Client::Score>(scoreOpt.value());
        auto text = std::static_pointer_cast<RenderEngine::TextComponent>(textOpt.value());
        scoreComp->_score = score;
        std::string scoreString = std::to_string(scoreComp->_score);
        std::string spacedScoreString;
        for(char c : scoreString) {
            spacedScoreString += c;
            spacedScoreString += " ";
        }
        spacedScoreString.pop_back();
        text->text = "S c o r e : " + spacedScoreString;
    }
    } catch (std::exception &e) {
        std::cout << "Error in UpdateScore : " << e.what() << std::endl;
    }
}
}
