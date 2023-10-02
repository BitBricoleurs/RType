/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Mob
*/

#include <iostream>
#include "EntityFactory.hpp"

namespace GameEngine {
    size_t EntityFactory::createBaseMob(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, int damageValue, float bulletStartX, float bulletStartY) {
            
        size_t entityId = createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);

        auto healthComponent = std::make_shared<HealthComponent>(maxHealth);
        auto damageComponent = std::make_shared<DamageComponent>(damageValue);
        auto bulletStartPositionComponent = std::make_shared<BulletStartPositionComponent>(bulletStartX, bulletStartY);

        engine.bindComponentToEntity(entityId, healthComponent->getComponentType(), healthComponent);
        engine.bindComponentToEntity(entityId, damageComponent->getComponentType(), damageComponent);
        engine.bindComponentToEntity(entityId, bulletStartPositionComponent->getComponentType(), bulletStartPositionComponent);

        return entityId;
    }

    size_t EntityFactory::createBossMob(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, int damageValue, float bulletStartX, float bulletStartY,
        int stageValue) {
            
        size_t entityId = createBaseMob(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight, maxHealth, damageValue, bulletStartX, bulletStartY);

        auto stageComponent = std::make_shared<BossStageComponent>(stageValue);
            
        engine.bindComponentToEntity(entityId, stageComponent->getComponentType(), stageComponent);

        return entityId;
    }

    size_t EntityFactory::createPlayer(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, float bulletStartX, float bulletStartY) {
            
        size_t entityId = createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);
            
        auto healthComponent = std::make_shared<HealthComponent>(maxHealth);
        auto bulletStartPositionComponent = std::make_shared<BulletStartPositionComponent>(bulletStartX, bulletStartY);

        engine.bindComponentToEntity(entityId, healthComponent->getComponentType(), healthComponent);
        engine.bindComponentToEntity(entityId, bulletStartPositionComponent->getComponentType(), bulletStartPositionComponent);

        return entityId;
    }

    size_t EntityFactory::createBullet(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int damageValue) {

        size_t entityId = createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);

        auto damageComponent = std::make_shared<DamageComponent>(damageValue);

        engine.bindComponentToEntity(entityId, damageComponent->getComponentType(), damageComponent);

        return entityId;        
    }

    size_t EntityFactory::createPowerUp(GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight) {
            
        return createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);
    }

    size_t EntityFactory::createBaseEntity(GameEngine& engine,const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight,  float posX, float posY, float velX, float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight) {

        std::vector<std::optional<std::shared_ptr<IComponent>>> components;
        auto rectComponent = std::make_shared<RectComponent>(rectX, rectY, rectWidth, rectHeight, spriteSheetPath);
        auto positionComponent = std::make_shared<PositionComponent>(posX, posY);
        auto velocityComponent = std::make_shared<VelocityComponent1>(velX, velY);
        auto directionComponent = std::make_shared<DirectionComponent>(dirX, dirY);
        auto hitboxComponent = std::make_shared<HitboxComponent>(hitboxWidth, hitboxHeight);
        components.push_back(rectComponent);
        components.push_back(positionComponent);
        components.push_back(velocityComponent);
        components.push_back(directionComponent);
        components.push_back(hitboxComponent);

        return engine.createEntity(components);
    }
};
