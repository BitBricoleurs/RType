//
// Created by Clément Lagasse on 03/11/2023.
//

#include "PaddingMenu.hpp"

namespace Client {

    size_t PaddingMenu::getComponentType() {
      return GameEngine::ComponentsType::getNewComponentType("PaddingMenu");
    }
}