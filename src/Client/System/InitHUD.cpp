//
// Created by alexandre on 14/10/23.
//

#include "InitHUD.hpp"

namespace Client {

    void InitHUD::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        auto rotation = 0.0;
        auto tint = Utils::ColorR(255,255,255,255);
        auto chargingBarEntityLayer1 = componentsContainer.createEntity();
        auto chargingBarEntityLayer2 = componentsContainer.createEntity();
        auto scoreEntity = componentsContainer.createEntity();

        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/hud.json");

            auto &factory = EntityFactory::getInstance();

            size_t healthBarEntity = factory.createHealthBar(componentsContainer, data.getString("/healthBar/spritePath"), 
                data.getInt("/healthBar/spriteSheetHeight"), data.getInt("/healthBar/spriteSheetWidth"), data.getInt("/healthBar/frames"),
                Utils::Vect2(data.getFloat("/healthBar/pos/x"), data.getFloat("/healthBar/pos/y")),
                data.getFloat("/healthBar/scale"), data.getFloat("/healthBar/rotation"), Utils::ColorR{static_cast<unsigned char>(data.getInt("/healthBar/tint/r")),
                static_cast<unsigned char>(data.getInt("/healthBar/tint/g")), static_cast<unsigned char>(data.getInt("/healthBar/tint/b")),
                static_cast<unsigned char>(data.getInt("/healthBar/tint/a"))}, data.getInt("/healthBar/layer"));
            eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("HealthBar"), healthBarEntity));

            componentsContainer.bindComponentToEntity(chargingBarEntityLayer1, std::make_shared<IsChargingBar>());
            componentsContainer.bindComponentToEntity(chargingBarEntityLayer1, std::make_shared<RenderEngine::SpriteComponent>(data.getString("/chargeBar/blueBar/spritePath"), Utils::Vect2(data.getFloat("/chargeBar/blueBar/pos/x"), data.getFloat("/chargeBar/blueBar/pos/y")), Utils::rect(data.getFloat("/chargeBar/blueBar/rect/x"), data.getFloat("/chargeBar/blueBar/rect/y"), data.getFloat("/chargeBar/blueBar/rect/w"), data.getFloat("/chargeBar/blueBar/rect/h")), data.getInt("/chargeBar/blueBar/layer"), data.getFloat("/chargeBar/blueBar/scale"), data.getFloat("/chargeBar/blueBar/rotation"), Utils::ColorR{static_cast<unsigned char>(data.getInt("/chargeBar/blueBar/tint/r")), static_cast<unsigned char>(data.getInt("/chargeBar/blueBar/tint/g")), static_cast<unsigned char>(data.getInt("/chargeBar/blueBar/tint/b")), static_cast<unsigned char>(data.getInt("/chargeBar/blueBar/tint/a"))}));
            componentsContainer.bindComponentToEntity(chargingBarEntityLayer2, std::make_shared<RenderEngine::SpriteComponent>(data.getString("/chargeBar/emptyBar/spritePath"), Utils::Vect2(data.getFloat("/chargeBar/emptyBar/pos/x"), data.getFloat("/chargeBar/emptyBar/pos/y")), Utils::rect(data.getFloat("/chargeBar/emptyBar/rect/x"), data.getFloat("/chargeBar/emptyBar/rect/y"), data.getFloat("/chargeBar/emptyBar/rect/w"), data.getFloat("/chargeBar/emptyBar/rect/h")), data.getInt("/chargeBar/emptyBar/layer"), data.getFloat("/chargeBar/emptyBar/scale"), data.getFloat("/chargeBar/emptyBar/rotation"), Utils::ColorR{static_cast<unsigned char>(data.getInt("/chargeBar/emptyBar/tint/r")), static_cast<unsigned char>(data.getInt("/chargeBar/emptyBar/tint/g")), static_cast<unsigned char>(data.getInt("/chargeBar/emptyBar/tint/b")), static_cast<unsigned char>(data.getInt("/chargeBar/emptyBar/tint/a"))}));
            componentsContainer.bindComponentToEntity(scoreEntity, std::make_shared<Score>());
            componentsContainer.bindComponentToEntity(scoreEntity, std::make_shared<RenderEngine::TextComponent>(data.getString("/score/defaultScore"), Utils::Vect2(data.getFloat("/score/scorePos/x"), data.getFloat("/score/scorePos/y")), data.getInt("/score/fontSize"), data.getInt("/score/layer"), Utils::ColorR{static_cast<unsigned char>(data.getInt("/score/tint/r")), static_cast<unsigned char>(data.getInt("/score/tint/g")), static_cast<unsigned char>(data.getInt("/score/tint/b")), static_cast<unsigned char>(data.getInt("/score/tint/a"))}));
            componentsContainer.bindComponentToEntity(healthBarEntity, std::make_shared<isHealthBar>());
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(1);
        }
    }

}
