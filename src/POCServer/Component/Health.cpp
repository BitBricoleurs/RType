//
// Created by alexandre on 03/10/23.
//

#include "Health.hpp"

Health::Health(int maxHealth) : maxHealth(maxHealth), currentHealth(maxHealth) {}

size_t Health::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("Health");
}
