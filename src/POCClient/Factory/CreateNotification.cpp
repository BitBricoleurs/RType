//
// Created by Clément Lagasse on 02/11/2023.
//

#include "EntityFactory.hpp"
#include "PlayNotifAnimation.hpp"
#include "LoseNotifAnimation.hpp"
#include "WinNotifAnimation.hpp"

size_t Client::EntityFactory::createPlayNotification(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/playNotification.json");

        size_t id = container.createEntity();
        int layer = data.getInt("/createPlay/layer");
        std::string spriteSheetPath;
        Utils::rect spriteRect = Utils::rect(0,
                                             0,
                                             data.getInt("/createPlay/hitboxWidth"),
                                             data.getInt("/createPlay/hitboxHeight"));
        int scale = data.getInt("/createPlay/scale");
        int rotation = 0;
        Utils::ColorR tint = Utils::ColorR(255, 255, 255, 255);
        Utils::Vect2 spritePos = {data.getFloat("/createPlay/spritePosX"), data.getFloat("/createPlay/spritePosY")};
        int numberImages = data.getInt("/createPlay/numberImages");

        std::vector<std::shared_ptr<RenderEngine::SpriteComponent>> spriteComponents;
        std::vector<int> nbrFramePerImages;
        std::vector<Utils::Vect2> spriteSheetSize;
        for (int i = 0; i < numberImages; i++) {
            std::string indexStr = std::to_string(i);
            spriteSheetPath = data.getString("/createPlay/images/" + indexStr + "/spriteSheetPath");
            auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
              spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(layer), scale,
              rotation, tint);
            spriteComponent->isVisible =  false;
            spriteComponents.push_back(spriteComponent);
            nbrFramePerImages.push_back(data.getInt("/createPlay/images/" + indexStr + "/frame"));
            spriteSheetSize.push_back(Utils::Vect2(data.getInt("/createPlay/images/" + indexStr + "/spriteSheetWidth"),
                                                   data.getInt("/createPlay/images/" + indexStr + "/spriteSheetHeight")));
        }

        auto spriteAnimationComponent = std::make_shared<Client::PlayNotifAnimation>();
        spriteAnimationComponent->currentImagesIndex = -1;
        spriteAnimationComponent->nbrImages = numberImages;
        spriteAnimationComponent->currentFrameIndex = 0;
        spriteAnimationComponent->nbrFramePerImages = nbrFramePerImages;
        spriteAnimationComponent->spriteSheetSize = spriteSheetSize;
        spriteAnimationComponent->spriteComponents = spriteComponents;

        container.bindComponentToEntity(id, spriteAnimationComponent);


        return id;

    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createPlayNotif: " << e.what() << std::endl;
        exit(1);
    }
}

size_t Client::EntityFactory::createLoseNotification(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/loseNotification.json");

        size_t id = container.createEntity();
        int layer = data.getInt("/createLose/layer");
        std::string spriteSheetPath;
        Utils::rect spriteRect = Utils::rect(0,
                                             0,
                                             data.getInt("/createLose/hitboxWidth"),
                                             data.getInt("/createLose/hitboxHeight"));
        int scale = data.getInt("/createLose/scale");
        int rotation = 0;
        Utils::ColorR tint = Utils::ColorR(255, 255, 255, 255);
        Utils::Vect2 spritePos = {data.getFloat("/createLose/spritePosX"), data.getFloat("/createLose/spritePosY")};
        int numberImages = data.getInt("/createLose/numberImages");

        std::vector<std::shared_ptr<RenderEngine::SpriteComponent>> spriteComponents;
        std::vector<int> nbrFramePerImages;
        std::vector<Utils::Vect2> spriteSheetSize;
        for (int i = 0; i < numberImages; i++) {
            std::string indexStr = std::to_string(i);
            spriteSheetPath = data.getString("/createLose/images/" + indexStr + "/spriteSheetPath");
            auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
              spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(layer), scale,
              rotation, tint);
            spriteComponent->isVisible =  false;
            spriteComponents.push_back(spriteComponent);
            nbrFramePerImages.push_back(data.getInt("/createLose/images/" + indexStr + "/frame"));
            spriteSheetSize.push_back(Utils::Vect2(data.getInt("/createLose/images/" + indexStr + "/spriteSheetWidth"),
                                                   data.getInt("/createLose/images/" + indexStr + "/spriteSheetHeight")));
        }

        auto spriteAnimationComponent = std::make_shared<Client::LoseNotifAnimation>();
        spriteAnimationComponent->currentImagesIndex = -1;
        spriteAnimationComponent->nbrImages = numberImages;
        spriteAnimationComponent->currentFrameIndex = 0;
        spriteAnimationComponent->nbrFramePerImages = nbrFramePerImages;
        spriteAnimationComponent->spriteSheetSize = spriteSheetSize;
        spriteAnimationComponent->spriteComponents = spriteComponents;

        container.bindComponentToEntity(id, spriteAnimationComponent);


        return id;

    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createLoseNotif: " << e.what() << std::endl;
        exit(1);
    }
}

size_t Client::EntityFactory::createWinNotification(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler)
{
        try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/winNotification.json");

        size_t id = container.createEntity();
        int layer = data.getInt("/createWin/layer");
        std::string spriteSheetPath;
        Utils::rect spriteRect = Utils::rect(0,
                                             0,
                                             data.getInt("/createWin/hitboxWidth"),
                                             data.getInt("/createWin/hitboxHeight"));
        int scale = data.getInt("/createWin/scale");
        int rotation = 0;
        Utils::ColorR tint = Utils::ColorR(255, 255, 255, 255);
        Utils::Vect2 spritePos = {data.getFloat("/createWin/spritePosX"), data.getFloat("/createWin/spritePosY")};
        int numberImages = data.getInt("/createWin/numberImages");

        std::vector<std::shared_ptr<RenderEngine::SpriteComponent>> spriteComponents;
        std::vector<int> nbrFramePerImages;
        std::vector<Utils::Vect2> spriteSheetSize;
        for (int i = 0; i < numberImages; i++) {
            std::string indexStr = std::to_string(i);
            spriteSheetPath = data.getString("/createWin/images/" + indexStr + "/spriteSheetPath");
            auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
              spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(layer), scale,
              rotation, tint);
            spriteComponent->isVisible =  false;
            spriteComponents.push_back(spriteComponent);
            nbrFramePerImages.push_back(data.getInt("/createWin/images/" + indexStr + "/frame"));
            spriteSheetSize.push_back(Utils::Vect2(data.getInt("/createWin/images/" + indexStr + "/spriteSheetWidth"),
                                                   data.getInt("/createWin/images/" + indexStr + "/spriteSheetHeight")));
        }

        auto spriteAnimationComponent = std::make_shared<Client::WinNotifAnimation>();
        spriteAnimationComponent->currentImagesIndex = -1;
        spriteAnimationComponent->nbrImages = numberImages;
        spriteAnimationComponent->currentFrameIndex = 0;
        spriteAnimationComponent->nbrFramePerImages = nbrFramePerImages;
        spriteAnimationComponent->spriteSheetSize = spriteSheetSize;
        spriteAnimationComponent->spriteComponents = spriteComponents;

        container.bindComponentToEntity(id, spriteAnimationComponent);


        return id;

    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createWinNotif: " << e.what() << std::endl;
        exit(1);
    }
}