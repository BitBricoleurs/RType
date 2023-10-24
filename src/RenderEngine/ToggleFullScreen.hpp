//
// Created by alexandre on 06/10/23.
//

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "WindowInfoComponent.hpp"
#include "raylib.h"

namespace RenderEngine {
class ToggleFullScreen : public GameEngine::ISystem {
public:
  ToggleFullScreen() = default;
  ~ToggleFullScreen() = default;

  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;

private:
};
} // namespace RenderEngine
