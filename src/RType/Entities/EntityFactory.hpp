/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntityFactory
*/

#ifndef ENTITYFACTORY_HPP_
#define ENTITYFACTORY_HPP_

#include <iostream>
#include "GameEngine.hpp"
#include "ComponentsType.hpp"
#include "EntityComponents.hpp"
#include "Vec2f.hpp"

class EntityFactory {
  public:
    EntityFactory() = default;
    ~EntityFactory() = default;
    size_t createBaseMob(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, int damageValue, float bulletStartX, float bulletStartY);

    size_t createBossMob(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, int damageValue, float bulletStartX, float bulletStartY,
        int stageValue);

    size_t createPlayer(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, float bulletStartX, float bulletStartY);

    size_t createBullet(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int damageValue);

    size_t createPowerUp(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight);

  protected:

  private:
    size_t createBaseEntity(GameEngine& engine,const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth,
        int rectHeight,  float posX, float posY, float velX, float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight);
};

#endif /* !ENTITYFACTORY_HPP_ */
