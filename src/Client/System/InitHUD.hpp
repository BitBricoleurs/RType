//
// Created by alexandre on 14/10/23.
//


#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "IsChargingBar.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "Score.hpp"
#include "isHealthBar.hpp"
#include "LoadConfig.hpp"
#include "EntityFactory.hpp"

    namespace Client {

    class InitHUD : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    public:

    private:
      bool done = false;
    };

}
