//
// Created by Clément Lagasse on 25/10/2023.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "RenderEngine.hpp"

namespace Client {

    class InputText : public GameEngine::AComponent {
    public:
      InputText(int maxSizeInput, int nbrSection, int maxSizeSection, char sectionDelimiter);

      size_t getComponentType() override;

      int _maxSizeInput;
      int _nbrSection;
      int _maxSizeSection;
      char _sectionDelimiter;
      int _cursorIndex;
      int _cursorSection;
      std::vector<std::vector<char>> _inPutSection;
    };
}
