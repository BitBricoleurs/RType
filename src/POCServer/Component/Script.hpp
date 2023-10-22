/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Script
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <cstddef>
#include <string>

namespace Server {

class Script : public GameEngine::AComponent {
public:
  Script(std::string script) : script(script) {}

  size_t getComponentType() override;
  std::string script;
};
} // namespace Server
