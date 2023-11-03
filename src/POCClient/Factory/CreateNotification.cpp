//
// Created by Clément Lagasse on 02/11/2023.
//

#include "EntityFactory.hpp"
#include "PlayNotifAnimation.hpp"

size_t Client::EntityFactory::createPlayNotification(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, Utils::Vect2 pos)
{
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/playNotification.json");

        size_t id = container.createEntity();
        int layer = data.getInt("/createPlay/layer");
        Utils::Vect2 spritePos = pos;
        std::string spriteSheetPath = data.getString("/createPlay/spriteSheetPath");
        Utils::rect spriteRect = Utils::rect(0,
                                             0,
                                             data.getInt("/createPlay/hitboxWidth"),
                                             data.getInt("/createPlay/hitboxHeight"));
        int scale = data.getInt("/createPlay/scale");
        int rotation = 0;
        Utils::ColorR tint = Utils::ColorR(255, 255, 255, 255);

        auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
          spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(layer), scale,
          rotation, tint);

        spriteComponent->isVisible =  true;

        auto spriteAnimationComponent = std::make_shared<Client::PlayNotifAnimation>();
        spriteAnimationComponent->frameHeight = data.getInt("/createPlay/hitboxHeight");
        spriteAnimationComponent->frameWidth = data.getInt("/createPlay/hitboxWidth");
        spriteAnimationComponent->currentFrameIndex = 0;
        spriteAnimationComponent->frames = data.getInt("/createPlay/animateFrame");
        spriteAnimationComponent->currentFrame.x = 0;
        spriteAnimationComponent->currentFrame.y = 0;
        spriteAnimationComponent->activatedFrame = data.getInt("/createPlay/staticFrame");

        container.bindComponentToEntity(id, spriteAnimationComponent);
        container.bindComponentToEntity(id, spriteComponent);

        return id;

    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createPlayerBullet: " << e.what() << std::endl;
        exit(1);
    }
}