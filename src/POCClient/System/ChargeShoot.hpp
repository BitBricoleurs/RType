//
// Created by Theophilus Homawoo on 12/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "Message.hpp"
#include "EventHandler.hpp"
#include "BulletUtils.hpp"

class ChargeShoot : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
};