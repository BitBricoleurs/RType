//
// Created by Clément Lagasse on 25/10/2023.
//

#pragma once

#include <cstddef>
#include <memory>
#include "unordered_map"
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "GameEngine.hpp"

namespace Client {

    class MenuNavigation : public GameEngine::AComponent {
    public:
      MenuNavigation() = default;

      size_t getComponentType() override;

      std::unordered_map<std::string, size_t> _mapNav = {
              {"LEFT", 0},
              {"RIGHT", 0},
              {"UP", 0},
              {"DOWN", 0}
      };
    };
    class MenuNavigationMethods {
        public:
        static void setMenuNavigation(size_t entityId, size_t entityIdToNavigate, std::string whereNavigate, GameEngine::ComponentsContainer &componentsContainer);
        };

}
