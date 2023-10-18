//
// Created by alexandre on 14/10/23.
//

#include "InitHUD.hpp"

void InitHUD::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto chargingBarEntityLayer1 = componentsContainer.createEntity();
    auto chargingBarEntityLayer2 = componentsContainer.createEntity();
    auto emptyHealthBarEntity = componentsContainer.createEntity();
    auto healthBarEntity = componentsContainer.createEntity();
    auto scoreEntity = componentsContainer.createEntity();

    try {
        ConfigData data = LoadConfig::getInstance().loadConfig("config/Game/hud.json");

        componentsContainer.bindComponentToEntity(chargingBarEntityLayer1, std::make_shared<IsChargingBar>());
        componentsContainer.bindComponentToEntity(chargingBarEntityLayer1, std::make_shared<GameEngine::SpriteComponent>(data.getString("/chargeBar/blueBar/spritePath"), GameEngine::Vect2(data.getFloat("/chargeBar/blueBar/pos/x"), data.getFloat("/chargeBar/blueBar/pos/y")), GameEngine::rect(data.getFloat("/chargeBar/blueBar/rect/x"), data.getFloat("/chargeBar/blueBar/rect/y"), data.getFloat("/chargeBar/blueBar/rect/w"), data.getFloat("/chargeBar/blueBar/rect/h")), data.getInt("/chargeBar/blueBar/layer"), data.getFloat("/chargeBar/blueBar/scale"), data.getFloat("/chargeBar/blueBar/rotation"), GameEngine::ColorR{static_cast<unsigned char>(data.getInt("/chargeBar/blueBar/tint/r")), static_cast<unsigned char>(data.getInt("/chargeBar/blueBar/tint/g")), static_cast<unsigned char>(data.getInt("/chargeBar/blueBar/tint/b")), static_cast<unsigned char>(data.getInt("/chargeBar/blueBar/tint/a"))}));
        componentsContainer.bindComponentToEntity(chargingBarEntityLayer2, std::make_shared<GameEngine::SpriteComponent>(data.getString("/chargeBar/emptyBar/spritePath"), GameEngine::Vect2(data.getFloat("/chargeBar/emptyBar/pos/x"), data.getFloat("/chargeBar/emptyBar/pos/y")), GameEngine::rect(data.getFloat("/chargeBar/emptyBar/rect/x"), data.getFloat("/chargeBar/emptyBar/rect/y"), data.getFloat("/chargeBar/emptyBar/rect/w"), data.getFloat("/chargeBar/emptyBar/rect/h")), data.getInt("/chargeBar/emptyBar/layer"), data.getFloat("/chargeBar/emptyBar/scale"), data.getFloat("/chargeBar/emptyBar/rotation"), GameEngine::ColorR{static_cast<unsigned char>(data.getInt("/chargeBar/emptyBar/tint/r")), static_cast<unsigned char>(data.getInt("/chargeBar/emptyBar/tint/g")), static_cast<unsigned char>(data.getInt("/chargeBar/emptyBar/tint/b")), static_cast<unsigned char>(data.getInt("/chargeBar/emptyBar/tint/a"))}));
        componentsContainer.bindComponentToEntity(scoreEntity, std::make_shared<Score>());
        componentsContainer.bindComponentToEntity(scoreEntity, std::make_shared<GameEngine::TextComponent>(data.getString("/score/defaultScore"), GameEngine::Vect2(data.getFloat("/score/scorePos/x"), data.getFloat("/score/scorePos/y")), data.getInt("/score/fontSize"), data.getInt("/score/layer"), GameEngine::ColorR{static_cast<unsigned char>(data.getInt("/score/tint/r")), static_cast<unsigned char>(data.getInt("/score/tint/g")), static_cast<unsigned char>(data.getInt("/score/tint/b")), static_cast<unsigned char>(data.getInt("/score/tint/a"))}));
        componentsContainer.bindComponentToEntity(emptyHealthBarEntity, std::make_shared<GameEngine::SpriteComponent>(data.getString("/healthBar/healthBar/spritePath"), GameEngine::Vect2(data.getFloat("/healthBar/healthBar/pos/x"), data.getFloat("/healthBar/healthBar/pos/y")), GameEngine::rect(data.getFloat("/healthBar/healthBar/rect/x"), data.getFloat("/healthBar/healthBar/rect/y"), data.getFloat("/healthBar/healthBar/rect/w"), data.getFloat("/healthBar/healthBar/rect/h")), data.getInt("/healthBar/healthBar/layer"), data.getFloat("/healthBar/healthBar/scale"), data.getFloat("/healthBar/healthBar/rotation"), GameEngine::ColorR{static_cast<unsigned char>(data.getInt("/healthBar/healthBar/tint/r")), static_cast<unsigned char>(data.getInt("/healthBar/healthBar/tint/g")), static_cast<unsigned char>(data.getInt("/healthBar/healthBar/tint/b")), static_cast<unsigned char>(data.getInt("/healthBar/healthBar/tint/a"))}));
        componentsContainer.bindComponentToEntity(healthBarEntity, std::make_shared<GameEngine::SpriteComponent>(data.getString("/healthBar/fullHealthBar/spritePath"), GameEngine::Vect2(data.getFloat("/healthBar/fullHealthBar/pos/x"), data.getFloat("/healthBar/fullHealthBar/pos/y")), GameEngine::rect(data.getFloat("/healthBar/fullHealthBar/rect/x"), data.getFloat("/healthBar/fullHealthBar/rect/y"), data.getFloat("/healthBar/fullHealthBar/rect/w"), data.getFloat("/healthBar/fullHealthBar/rect/h")), data.getInt("/healthBar/fullHealthBar/layer"), data.getFloat("/healthBar/fullHealthBar/scale"), data.getFloat("/healthBar/fullHealthBar/rotation"), GameEngine::ColorR{static_cast<unsigned char>(data.getInt("/healthBar/fullHealthBar/tint/r")), static_cast<unsigned char>(data.getInt("/healthBar/fullHealthBar/tint/g")), static_cast<unsigned char>(data.getInt("/healthBar/fullHealthBar/tint/b")), static_cast<unsigned char>(data.getInt("/healthBar/fullHealthBar/tint/a"))}));
        componentsContainer.bindComponentToEntity(healthBarEntity, std::make_shared<isHealthBar>());
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}
