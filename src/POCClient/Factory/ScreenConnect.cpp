//
// Created by Clément Lagasse on 24/10/2023.
//

#include "EntityFactory.hpp"
#include "SpriteComponent.hpp"
#include "IsBackgroundConnect.hpp"
#include "IsMenuConnect.hpp"
#include "IsMenuIp.hpp"
#include "IsMenuPort.hpp"
#include "IsButtonConnect.hpp"
#include "InputText.hpp"
#include "MenuNavigation.hpp"
#include "IsSelected.hpp"

size_t Client::EntityFactory::createBackGroundConnect(GameEngine::ComponentsContainer &container)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/ConnectScreen/createBackground.json");


        Utils::Vect2 spritePos(data.getInt("/background/spritePosX"), data.getInt("/background/spritePosY"));
        std::string spriteSheetPath = data.getString("/background/spritePath");
        Utils::Vect2 spriteRect(data.getInt("/background/spriteWidth"), data.getInt("/background/spriteWidth"));
        float scale = data.getFloat("/background/scale");
        int layer = data.getInt("/background/layer");
        float rotation = 0;
        Utils::ColorR tint(255, 255, 255, 255);
        Utils::rect rect(
            spritePos.x, spritePos.y, spriteRect.x, spriteRect.y);

        auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
          spriteSheetPath, spritePos, rect, static_cast<size_t>(layer), scale,
          rotation, tint);

        auto isBackgroundConnect = std::make_shared<Client::IsBackgroundConnect>();

        size_t entityId = container.createEntity();
        container.bindComponentToEntity(entityId, spriteComponent);
        container.bindComponentToEntity(entityId, isBackgroundConnect);

        return entityId;
    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createBackGroundConnect: " << e.what() << std::endl;
        exit(1);
    }
}

size_t Client::EntityFactory::createMenuConnect(GameEngine::ComponentsContainer &container)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/ConnectScreen/createMenu.json");

        Utils::Vect2 spritePos(data.getInt("/menu/spritePosX"), data.getInt("/menu/spritePosY"));
        std::string spriteSheetPath = data.getString("/menu/spritePath");
        Utils::Vect2 spriteRect(data.getInt("/menu/spriteWidth"), data.getInt("/menu/spriteWidth"));
        float scale = data.getFloat("/menu/scale");
        int layer = data.getInt("/menu/layer");
        float rotation = 0;
        Utils::ColorR tint(255, 255, 255, 255);
        Utils::rect rect(
            spritePos.x, spritePos.y, spriteRect.x, spriteRect.y);

        auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
            spriteSheetPath, spritePos, rect, static_cast<size_t>(layer), scale,
            rotation, tint);

        auto isMenuConnect = std::make_shared<Client::IsMenuConnect>();

        size_t entityId = container.createEntity();
        container.bindComponentToEntity(entityId, spriteComponent);
        container.bindComponentToEntity(entityId, isMenuConnect);
        return entityId;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

size_t Client::EntityFactory::createInputIp(GameEngine::ComponentsContainer &container)
{
    try {
    LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/ConnectScreen/createIpInput.json");

    std::string spriteSheetPath = data.getString("/ip_input/spritePath");
    Utils::Vect2 spritePos(data.getInt("/ip_input/spritePosX"), data.getInt("/ip_input/spritePosY"));

    Utils::Vect2 spriteRect(data.getInt("/ip_input/spriteSheetWidth"), data.getInt("/ip_input/spriteSheetHeight"));
    Utils::Vect2 spriteHitbox(data.getInt("/ip_input/hitboxHeight"), data.getInt("/ip_input/hitboxWidth"));
    float scale = data.getFloat("/ip_input/scale");
    int layer = data.getInt("/ip_input/layer");
    float rotation = 0;
    Utils::ColorR tint(255, 255, 255, 255);
    Utils::rect rect(0, 0, spriteHitbox.y, spriteHitbox.x);

    auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
            spriteSheetPath, spritePos, rect, static_cast<size_t>(layer), scale,
            rotation, tint);

    auto isIpInput = std::make_shared<Client::IsMenuIp>();

    int nbrSection = data.getInt("/ip_input/nbrSection");
    int maxSizeSection = data.getInt("/ip_input/maxSizeSection");
    char delimiter = data.getString("/ip_input/delimiter")[0];
    int maxSizeInput = data.getInt("/ip_input/maxSizeInput");
    Utils::Vect2 posText(data.getInt("/ip_input/relatixeTextPosX") + spritePos.x, data.getInt("/ip_input/relatixeTextPosY") + spritePos.y);

    auto inputText = std::make_shared<Client::InputText>(maxSizeInput, nbrSection, maxSizeSection, delimiter);
    auto text = std::make_shared<RenderEngine::TextComponent>("", posText, 30, layer + 1, tint);
    auto menuNavigation = std::make_shared<Client::MenuNavigation>();
    auto IsSelected =  std::make_shared<Client::IsSelected>();

    size_t entityId = container.createEntity();
    container.bindComponentToEntity(entityId, spriteComponent);
    container.bindComponentToEntity(entityId, isIpInput);
    container.bindComponentToEntity(entityId, text);
    container.bindComponentToEntity(entityId, inputText);
    container.bindComponentToEntity(entityId, menuNavigation);
    container.bindComponentToEntity(entityId, IsSelected);

    return entityId;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

size_t Client::EntityFactory::createInputPort(GameEngine::ComponentsContainer &container)
{
    try {
    LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/ConnectScreen/createPortInput.json");

    std::string spriteSheetPath = data.getString("/port_input/spritePath");
    Utils::Vect2 spritePos(data.getInt("/port_input/spritePosX"), data.getInt("/port_input/spritePosY"));

    Utils::Vect2 spriteRect(data.getInt("/port_input/spriteSheetWidth"), data.getInt("/port_input/spriteSheetHeight"));
    Utils::Vect2 spriteHitbox(data.getInt("/port_input/hitboxHeight"), data.getInt("/port_input/hitboxWidth"));
    float scale = data.getFloat("/port_input/scale");
    int layer = data.getInt("/port_input/layer");
    float rotation = 0;
    Utils::ColorR tint(255, 255, 255, 255);
    Utils::rect rect(0, 0, spriteHitbox.y, spriteHitbox.x);

    auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
            spriteSheetPath, spritePos, rect, static_cast<size_t>(layer), scale,
            rotation, tint);

    auto isIpInput = std::make_shared<Client::IsMenuPort>();

    int nbrSection = data.getInt("/port_input/nbrSection");
    int maxSizeSection = data.getInt("/port_input/maxSizeSection");
    char delimiter = data.getString("/port_input/delimiter")[0];
    int maxSizeInput = data.getInt("/port_input/maxSizeInput");
    Utils::Vect2 posText(data.getInt("/port_input/relatixeTextPosX") + spritePos.x, data.getInt("/port_input/relatixeTextPosY") + spritePos.y);

    auto inputText = std::make_shared<Client::InputText>(maxSizeInput, nbrSection, maxSizeSection, delimiter);
    auto text = std::make_shared<RenderEngine::TextComponent>("", posText, 30, layer + 1, tint);

    auto menuNavigation = std::make_shared<Client::MenuNavigation>();

    size_t entityId = container.createEntity();
    container.bindComponentToEntity(entityId, spriteComponent);
    container.bindComponentToEntity(entityId, isIpInput);
    container.bindComponentToEntity(entityId, menuNavigation);
    container.bindComponentToEntity(entityId, inputText);
    container.bindComponentToEntity(entityId, text);
    return entityId;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

size_t Client::EntityFactory::createConnectButton(GameEngine::ComponentsContainer &container)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/ConnectScreen/createButtonCon.json");

        Utils::Vect2 spritePos(data.getInt("/button_con/spritePosX"), data.getInt("/button_con/spritePosY"));
        std::string spriteSheetPath = data.getString("/button_con/spritePath");
        Utils::Vect2 hitboxWidth(data.getInt("/button_con/hitboxWidth"), data.getInt("/button_con/hitboxHeight"));
        Utils::Vect2 spriteRect(data.getInt("/button_con/spriteSheetWidth"), data.getInt("/button_con/spriteSheetHeight"));
        float scale = data.getFloat("/button_con/scale");
        int layer = data.getInt("/button_con/layer");
        float rotation = 0;
        Utils::ColorR tint(255, 255, 255, 255);

        Utils::rect rect(
            0, 0, hitboxWidth.x, hitboxWidth.y);

        auto button = std::make_shared<RenderEngine::ButtonComponent>(
            spriteSheetPath, spritePos, rect, static_cast<size_t>(layer), scale,
            rotation, tint);
        auto isButtonConnect = std::make_shared<Client::IsButtonConnect>();

        button->clickEvent = "CLICK_CONNECT";
        button->hoverEvent = "HOVER_CONNECT";
        button->normalEvent = "NORMAL_CONNECT";
        button->hoverColor = Utils::ColorR(255, 255, 255, 255);

        size_t entityId = container.createEntity();
        container.bindComponentToEntity(entityId, button);
        container.bindComponentToEntity(entityId, isButtonConnect);

        return entityId;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
