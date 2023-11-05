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

std::string Client::InputText::getText()
{
    std::string text;
    for (int i = 0; i < _nbrSection; i++) {
        for (int j = 0; j < _inPutSection[i].size(); j++) {
            text += _inPutSection[i][j];
        }
        if (_inPutSection.size() - 1 && i < _cursorSection)
            text += _sectionDelimiter;
    }
    return text;
}