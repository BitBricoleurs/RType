//
// Created by alexandre on 03/10/23.
//

#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include <cstddef>

#pragma once

class BossStage : public GameEngine::AComponent {
    public:
      BossStage(int stage);

      size_t getComponentType() override;

      int stage;
};
