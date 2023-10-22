/*
** EPITECH PROJECT, 2023
** RType
** File description:
** getEntitiesWithComponent
*/

#include "LuaFunctions.hpp"

// The function that we'll call from Lua to get entities
int l_getEntitiesWithComponent(lua_State *L) {

  // Call our actual function
  auto componentsContainer =
      *(reinterpret_cast<GameEngine::ComponentsContainer **>(
          lua_touserdata(L, 1)));

  // Second argument is the component name
  const char *componentName = luaL_checkstring(L, 2);

  // Call the actual function
  auto entities = componentsContainer->getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType(componentName));
  // We need to return this list to Lua; this might involve creating a Lua table
  // and setting each entity as an element of it. Here we just return one entity
  // for simplicity.
  if (!entities.empty()) {
    lua_pushlightuserdata(L, &entities);
  } else {
    lua_pushnil(L);
  }

  return 1; // Number of return values we've put on the stack
}