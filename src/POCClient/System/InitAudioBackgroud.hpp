//
// Created by Clément Lagasse on 15/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#ifndef _WIN32
#include "AudioComponent.hpp"
#endif
#include "LoadConfig.hpp"

namespace Client {

    class InitAudioBackgroud : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    public:

    private:
      bool done = false;
    };

}
