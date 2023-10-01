/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntityFactory
*/

#ifndef ENTITYFACTORY_HPP_
#define ENTITYFACTORY_HPP_

#include "EntityComponents.hpp"
#include "GameEngine.hpp"
#include "Vec2f.hpp"
#include <iostream>

class EntityFactory {
  public:
    static EntityFactory& getInstance() {
        static EntityFactory instance;
        return instance;
    }
    EntityFactory(const EntityFactory&) = delete;
    EntityFactory& operator=(const EntityFactory&) = delete;

    size_t createBaseMob(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int spriteSheetHeight,
                         int spriteSheetWidth, int frames, bool twoDirections, const std::string& deathSpriteSheetPath,
                         int deathSpriteSheetHeight, int deathSpriteSheetWidth, int deathFrames, float posX, float posY,
                         float velX, float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight,
                         int maxHealth, int damageValue, float bulletStartX, float bulletStartY);

    size_t createBossMob(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int spriteSheetHeight,
                         int spriteSheetWidth, int frames, bool twoDirections, const std::string& deathSpriteSheetPath,
                         int deathSpriteSheetHeight, int deathSpriteSheetWidth, int deathFrames, float posX, float posY,
                         float velX, float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight,
                         int maxHealth, int damageValue, float bulletStartX, float bulletStartY, int stageValue);

    size_t createPlayer(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int rectX, int rectY,
                        int rectWidth, int rectHeight, float posX, float posY, float velX, float velY, float dirX,
                        float dirY, float hitboxWidth, float hitboxHeight, int maxHealth, float bulletStartX,
                        float bulletStartY);

    size_t createBullet(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int rectX, int rectY,
                        int rectWidth, int rectHeight, float posX, float posY, float velX, float velY, float dirX,
                        float dirY, float hitboxWidth, float hitboxHeight, int damageValue);

    size_t createPowerUp(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int rectX, int rectY,
                         int rectWidth, int rectHeight, float posX, float posY, float velX, float velY, float dirX,
                         float dirY, float hitboxWidth, float hitboxHeight);

  private:
    EntityFactory() = default;
    ~EntityFactory() = default;
    size_t createBaseEntity(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int spriteSheetHeight,
                            int spriteSheetWidth, int frames, bool twoDirections, float posX, float posY, float velX,
                            float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight);

    std::shared_ptr<GameEngine::SpriteAnimationComponent> initAnimation(const std::string& spriteSheetPath, int frames,
                                                                        int width, int height, bool twoDirections,
                                                                        int direction);

    std::shared_ptr<GameEngine::DeathAnimationComponent>
    initDeathAnimation(const std::string& deathSpriteSheetPath, int deathFrames, int deathWidth, int deathHeight);
};

#endif /* !ENTITYFACTORY_HPP_ */
