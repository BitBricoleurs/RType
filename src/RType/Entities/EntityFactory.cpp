/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Mob
*/

#include <iostream>
#include "EntityFactory.hpp"


    size_t EntityFactory::createBaseMob(GameEngine::GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, int damageValue, float bulletStartX, float bulletStartY) {
            
        size_t entityId = createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);

        auto healthComponent = std::make_shared<GameEngine::HealthComponent>(maxHealth);
        healthComponent->setComponentType(GameEngine::ComponentsType::getComponentType("HealthComponent"));
        auto damageComponent = std::make_shared<GameEngine::DamageComponent>(damageValue);
        damageComponent->setComponentType(GameEngine::ComponentsType::getComponentType("DamageComponent"));
        auto bulletStartPositionComponent = std::make_shared<GameEngine::BulletStartPositionComponent>(bulletStartX, bulletStartY);
        bulletStartPositionComponent->setComponentType(GameEngine::ComponentsType::getComponentType("BulletStartPositionComponent"));

        engine.bindComponentToEntity(entityId, healthComponent->getComponentType(), healthComponent);
        engine.bindComponentToEntity(entityId, damageComponent->getComponentType(), damageComponent);
        engine.bindComponentToEntity(entityId, bulletStartPositionComponent->getComponentType(), bulletStartPositionComponent);

        return entityId;
    }

    size_t EntityFactory::createBossMob(GameEngine::GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, int damageValue, float bulletStartX, float bulletStartY,
        int stageValue) {
            
        size_t entityId = createBaseMob(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight, maxHealth, damageValue, bulletStartX, bulletStartY);

        auto stageComponent = std::make_shared<GameEngine::BossStageComponent>(stageValue);
        stageComponent->setComponentType(GameEngine::ComponentsType::getComponentType("BossStageComponent"));
            
        engine.bindComponentToEntity(entityId, stageComponent->getComponentType(), stageComponent);

        return entityId;
    }

    size_t EntityFactory::createPlayer(GameEngine::GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int maxHealth, float bulletStartX, float bulletStartY) {
            
        size_t entityId = createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);
            
        auto healthComponent = std::make_shared<GameEngine::HealthComponent>(maxHealth);
        healthComponent->setComponentType(GameEngine::ComponentsType::getComponentType("HealthComponent"));
        auto bulletStartPositionComponent = std::make_shared<GameEngine::BulletStartPositionComponent>(bulletStartX, bulletStartY);
        bulletStartPositionComponent->setComponentType(GameEngine::ComponentsType::getComponentType("BulletStartPositionComponent"));

        engine.bindComponentToEntity(entityId, healthComponent->getComponentType(), healthComponent);
        engine.bindComponentToEntity(entityId, bulletStartPositionComponent->getComponentType(), bulletStartPositionComponent);

        return entityId;
    }

    size_t EntityFactory::createBullet(GameEngine::GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight, int damageValue) {

        size_t entityId = createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);

        auto damageComponent = std::make_shared<GameEngine::DamageComponent>(damageValue);
        damageComponent->setComponentType(GameEngine::ComponentsType::getComponentType("DamageComponent"));

        engine.bindComponentToEntity(entityId, damageComponent->getComponentType(), damageComponent);

        return entityId;        
    }

    size_t EntityFactory::createPowerUp(GameEngine::GameEngine& engine, 
        const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight, 
        float posX, float posY, float velX, float velY, float dirX, float dirY, 
        float hitboxWidth, float hitboxHeight) {
            
        return createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);
    }

    size_t EntityFactory::createBaseEntity(GameEngine::GameEngine& engine,const std::string& spriteSheetPath, int rectX, int rectY, int rectWidth, int rectHeight,  float posX, float posY, float velX, float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight) {

        std::vector<std::optional<std::shared_ptr<GameEngine::IComponent>>> components;
        auto rectComponent = std::make_shared<GameEngine::RectComponent>(rectX, rectY, rectWidth, rectHeight, spriteSheetPath);
        auto positionComponent = std::make_shared<GameEngine::PositionComponent>(posX, posY);
        auto velocityComponent = std::make_shared<GameEngine::VelocityComponent>(velX, velY);
        auto directionComponent = std::make_shared<GameEngine::DirectionComponent>(dirX, dirY);
        auto hitboxComponent = std::make_shared<GameEngine::HitboxComponent>(hitboxWidth, hitboxHeight);
        auto collideComponent = std::make_shared<GameEngine::CollideComponent>();

        rectComponent->setComponentType(GameEngine::ComponentsType::getComponentType("RectComponent"));
        positionComponent->setComponentType(GameEngine::ComponentsType::getComponentType("PositionComponent"));
        velocityComponent->setComponentType(GameEngine::ComponentsType::getComponentType("VelocityComponent"));
        directionComponent->setComponentType(GameEngine::ComponentsType::getComponentType("DirectionComponent"));
        hitboxComponent->setComponentType(GameEngine::ComponentsType::getComponentType("HitboxComponent"));
        collideComponent->setComponentType(GameEngine::ComponentsType::getComponentType("CollideComponent"));

        components.push_back(rectComponent);
        components.push_back(positionComponent);
        components.push_back(velocityComponent);
        components.push_back(directionComponent);
        components.push_back(hitboxComponent);
        components.push_back(collideComponent);

        return engine.createEntity(components);
    }

