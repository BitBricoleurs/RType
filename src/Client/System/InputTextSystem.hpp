//
// Created by Clément Lagasse on 25/10/2023.
//

#pragma once

#include <unordered_map>
#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "LoadConfig.hpp"
#include "RenderEngine.hpp"
#include "InputText.hpp"

namespace Client {
    enum ActionType {
        DIGIT,
        DELETE,
        SEPARATOR,
        NOTFOUND
    };
    class InputTextSystem : public GameEngine::ISystem {
    public:
        InputTextSystem() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;

        std::unordered_map<Client::ActionType, std::function<void(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)>> ACTION_TO_MANAGE =
        {
            {Client::ActionType::DIGIT, [this](GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {manageDigit(componentsContainer, eventHandler);}},
            {Client::ActionType::SEPARATOR, [this](GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {manageSeparator(componentsContainer, eventHandler);}},
            {Client::ActionType::DELETE, [this](GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {manageDelete(componentsContainer, eventHandler);}},
            {Client::ActionType::NOTFOUND, [this](GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
                std::cerr << "Couldn't find action to this key but the key is binded to event" << std::endl;
                return;
            }}
        };
    private:
        void manageDigit(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler);
        void manageSeparator(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler);
        void manageDelete(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler);
        std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> getStringInputSelected(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler);
        void checkCurrentSectionFull(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair);
        bool checkWholeInputFull(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair);

        void checkDeleteCurrentSectionEmpty(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair);
        bool checkWholeInputEmpty(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair);
        void updateText(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair);
    };
}