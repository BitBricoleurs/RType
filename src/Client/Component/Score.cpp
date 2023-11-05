//
// Created by Theophilus Homawoo on 04/10/2023.
//

#include "Score.hpp"

namespace Client {

    size_t Score::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("Score");
    }

}