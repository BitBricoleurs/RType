//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "AComponent.hpp"
#include "SpriteComponent.hpp"
#include "IsPlayer.hpp"
#include "PositionComponent2D.hpp"
#include "BulletUtils.hpp"
#include "Message.hpp"
#include "Shooter.hpp"
#include "GameState.hpp"

namespace Client {

    class ChargingBar : public GameEngine::ISystem {
    public:
      void update(GameEngine::ComponentsContainer &componentsContainer,
                  GameEngine::EventHandler &eventHandler) override;

    private:
      int _charge = 0;
      int _maxCharge = 103;
      bool shoot = false;
      bool endShoot = true;
    };

}
