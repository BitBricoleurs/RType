//
// Created by alexandre on 14/10/23.
//

#include "InitHUD.hpp"

void InitHUD::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto rotation = 0.0;
    auto tint = GameEngine::ColorR(255,255,255,255);
    auto chargingBarEntityLayer1 = componentsContainer.createEntity();
    auto chargingBarEntityLayer2 = componentsContainer.createEntity();
    auto emptyHealthBarEntity = componentsContainer.createEntity();
    auto healthBarEntity = componentsContainer.createEntity();
    auto scoreEntity = componentsContainer.createEntity();

    componentsContainer.bindComponentToEntity(chargingBarEntityLayer1, std::make_shared<IsChargingBar>());
    componentsContainer.bindComponentToEntity(chargingBarEntityLayer1, std::make_shared<GameEngine::SpriteComponent>("assets/HUD/BlueBar.png", GameEngine::Vect2(752, 990), GameEngine::rect(0, 0, 0, 26), 100, 2.0f, rotation, tint));
    componentsContainer.bindComponentToEntity(chargingBarEntityLayer2, std::make_shared<GameEngine::SpriteComponent>("assets/HUD/EmptyBar.png", GameEngine::Vect2(752, 990), GameEngine::rect(0, 0, 208, 26), 99, 2.0f, rotation, tint));
    componentsContainer.bindComponentToEntity(scoreEntity, std::make_shared<Score>());
    componentsContainer.bindComponentToEntity(scoreEntity, std::make_shared<GameEngine::TextComponent>("Score: 0", GameEngine::Vect2(800, 0), 64, 100, GameEngine::ColorR{255, 255, 255, 255}));
    componentsContainer.bindComponentToEntity(emptyHealthBarEntity, std::make_shared<GameEngine::SpriteComponent>("assets/HUD/HealthBar.png", GameEngine::Vect2(0,990), GameEngine::rect(0, 0, 24, 10), 99, 4.0f, rotation, tint));
    componentsContainer.bindComponentToEntity(healthBarEntity, std::make_shared<GameEngine::SpriteComponent>("assets/HUD/FullHealthBar.png", GameEngine::Vect2(0,990), GameEngine::rect(0, 0, 24, 10), 100, 4.0f, rotation, tint));
    componentsContainer.bindComponentToEntity(healthBarEntity, std::make_shared<isHealthBar>());


}