//
// Created by Clément Lagasse on 25/10/2023.
//

#include "InputTextSystem.hpp"


static const std::unordered_map<std::string, Client::ActionType> MAP_ACTION =
        {
            {"DELETE_KEY_PRESSED", Client::ActionType::DELETE},
            {"S_KEY_PRESSED", Client::ActionType::DELETE},
            {"ZERO_KEY_PRESSED", Client::ActionType::DIGIT},
            {"ONE_KEY_PRESSED", Client::ActionType::DIGIT},
            {"TWO_KEY_PRESSED", Client::ActionType::DIGIT},
            {"THREE_KEY_PRESSED", Client::ActionType::DIGIT},
            {"FOUR_KEY_PRESSED", Client::ActionType::DIGIT},
            {"FIVE_KEY_PRESSED", Client::ActionType::DIGIT},
            {"SIX_KEY_PRESSED", Client::ActionType::DIGIT},
            {"SEVEN_KEY_PRESSED", Client::ActionType::DIGIT},
            {"EIGHT_KEY_PRESSED", Client::ActionType::DIGIT},
            {"NINE_KEY_PRESSED", Client::ActionType::DIGIT},
            {"SPACE_KEY_PRESSED", Client::ActionType::SEPARATOR}
        };

static const std::unordered_map<std::string, char> MAP_DIGIT =
        {
        {"ZERO_KEY_PRESSED", '0'},
        {"ONE_KEY_PRESSED", '1'},
        {"TWO_KEY_PRESSED", '2'},
        {"THREE_KEY_PRESSED", '3'},
        {"FOUR_KEY_PRESSED", '4'},
        {"FIVE_KEY_PRESSED", '5'},
        {"SIX_KEY_PRESSED", '6'},
        {"SEVEN_KEY_PRESSED", '7'},
        {"EIGHT_KEY_PRESSED", '8'},
        {"NINE_KEY_PRESSED", '9'},
        };



void Client::InputTextSystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto event = eventHandler.getTriggeredEvent();
    ActionType action = NOTFOUND;

    for (auto &key : MAP_ACTION) {
        if (key.first == event.first) {
            action = key.second;
        }
    }
    for (auto &key : this->ACTION_TO_MANAGE) {
        if (key.first == action) {
            key.second(componentsContainer, eventHandler);
        }
    }
}

std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> Client::InputTextSystem::getStringInputSelected(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto event = eventHandler.getTriggeredEvent();
    auto selectType = GameEngine::ComponentsType::getComponentType("IsSelected");

    auto entities = componentsContainer.getEntitiesWithComponent(selectType);
    if (entities.empty())
        throw std::runtime_error("Error while trying to getStringInput on not selected entities");
    if (entities.size() > 1) {
        eventHandler.queueEvent("UPDATE_SELECT");
        eventHandler.queueEvent(event.first, event.second);
        throw std::runtime_error("Error while trying to getStringInput on multiple selected entities");
    }
    // Get Text
    auto textCompType = GameEngine::ComponentsType::getComponentType("TextComponent");
    auto mayComp = componentsContainer.getComponent(entities[0], textCompType);
    if (!mayComp.has_value()) {
        throw std::runtime_error("Error while trying to getStringInput on selectedEntities that not have TextComponent");
    }
    auto comp = mayComp.value();
    auto textComp = std::static_pointer_cast<RenderEngine::TextComponent>(comp);
    // Get InputText comp
    auto inputCompType = GameEngine::ComponentsType::getComponentType("InputText");
    auto mayCompInput = componentsContainer.getComponent(entities[0], inputCompType);
    if (!mayCompInput.has_value()) {
        throw std::runtime_error("Error while trying to getStringInput on selectedEntities that not have InputText");
    }
    auto compInput = mayCompInput.value();
    auto inputComp = std::static_pointer_cast<Client::InputText>(compInput);
    return std::make_pair(inputComp, textComp);
}

void Client::InputTextSystem::manageDelete(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto event = eventHandler.getTriggeredEvent();

    try {
        auto textToChange = getStringInputSelected(componentsContainer, eventHandler);
        if (checkWholeInputEmpty(textToChange)) {
            return;
        }
        checkDeleteCurrentSectionEmpty(textToChange);
        textToChange.first->_inPutSection[textToChange.first->_cursorSection].pop_back();
        updateText(textToChange);

    } catch (std::runtime_error &e) {
            std::cerr << "[ERROR] InputTextSystem: " << e.what() << std::endl;
    }
}

void Client::InputTextSystem::manageDigit(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto event = eventHandler.getTriggeredEvent();
    char digitToAppend = 0;

    for (auto &key : MAP_DIGIT) {
        if (event.first == key.first) {
            digitToAppend = key.second;
        }
    }
    if (digitToAppend == 0) {
        std::cerr << "Error while mapping Digit check InputTextSystem.cpp" << std::endl;
        return;
    }
    try {
        auto textToChange = getStringInputSelected(componentsContainer, eventHandler);
        if (checkWholeInputFull(textToChange)) {
            return;
        }
        checkCurrentSectionFull(textToChange);
        textToChange.first->_inPutSection[textToChange.first->_cursorSection].push_back(digitToAppend);
        updateText(textToChange);
        auto text2ToChange = getStringInputSelected(componentsContainer, eventHandler);
    } catch (std::runtime_error &e) {
            std::cerr << "[ERROR] InputTextSystem: " << e.what() << std::endl;
    }
}

void Client::InputTextSystem::manageSeparator(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
     try {
        auto textToChange = getStringInputSelected(componentsContainer, eventHandler);
        if (textToChange.first->_cursorSection + 1 < textToChange.first->_nbrSection && !textToChange.first->_inPutSection[textToChange.first->_cursorSection].empty()) {
            textToChange.first->_cursorSection++;
            updateText(textToChange);
        }
    } catch (std::runtime_error &e) {
            std::cerr << "[ERROR] InputTextSystem: " << e.what() << std::endl;
    }
}

bool Client::InputTextSystem::checkWholeInputFull(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair)
{
    if (pair.first->_inPutSection[pair.first->_nbrSection - 1].size() == pair.first->_maxSizeSection) {
        return true;
    }
    return false;
}

bool Client::InputTextSystem::checkWholeInputEmpty(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair)
{
    size_t count = 0;
    for (auto &vec : pair.first->_inPutSection) {
        count += vec.size();
    }
    if (count > 0)
        return false;
    return true;
}

void Client::InputTextSystem::checkCurrentSectionFull(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair)
{
    if (pair.first->_inPutSection[pair.first->_cursorSection].size() == pair.first->_maxSizeSection) {
        if (pair.first->_cursorSection < pair.first->_nbrSection)
            pair.first->_cursorSection++;
    }

}

void Client::InputTextSystem::checkDeleteCurrentSectionEmpty(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair)
{
    if (pair.first->_inPutSection[pair.first->_cursorSection].empty()) {
        pair.first->_cursorSection--;
    }
}

void Client::InputTextSystem::updateText(std::pair<std::shared_ptr<Client::InputText>, std::shared_ptr<RenderEngine::TextComponent>> &pair)
{
    std::string newStr;

    for (size_t i = 0; i <= pair.first->_cursorSection; ++i) {
        for (size_t j = 0; j < pair.first->_inPutSection[i].size(); ++j) {
            newStr += pair.first->_inPutSection[i][j];
            if (j < pair.first->_inPutSection[i].size() - 1) {
                newStr += " ";
            }
        }
        if (i < pair.first->_inPutSection.size() - 1 && i < pair.first->_cursorSection) {
            newStr += ' ';
            newStr += pair.first->_sectionDelimiter;
            newStr += ' ';
        }
    }
    pair.second->text = newStr;
}
