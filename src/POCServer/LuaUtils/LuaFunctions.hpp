/*
** EPITECH PROJECT, 2023
** RType
** File description:
** functions
*/

#pragma once

#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "GameEngine.hpp"
#include "lua.hpp"

int getEntitiesWithComponent(lua_State *L);
int getComponent(lua_State *L);
