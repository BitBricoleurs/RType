//
// Created by Clément Lagasse on 25/10/2023.
//

#include "InputText.hpp"

Client::InputText::InputText(int maxSizeInput, int nbrSection, int maxSizeSection, char sectionDelimiter)
: _maxSizeInput(maxSizeInput), _maxSizeSection(maxSizeSection), _nbrSection(nbrSection), _sectionDelimiter(sectionDelimiter), _cursorIndex(0), _cursorSection(0)
{
    _inPutSection.resize(_nbrSection);
}

size_t Client::InputText::getComponentType()
{
    return GameEngine::ComponentsType::getNewComponentType("InputText");
}