/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Mob
*/

#include "EntityFactory.hpp"
#include <iostream>
#include <memory>

size_t EntityFactory::createBaseMob(GameEngine::GameEngine& engine, const std::string& spriteSheetPath,
                                    int spriteSheetHeight, int spriteSheetWidth, int frames, bool twoDirections,
                                    const std::string& deathSpriteSheetPath, int deathSpriteSheetHeight,
                                    int deathSpriteSheetWidth, int deathFrames, float posX, float posY, float velX,
                                    float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight,
                                    int maxHealth, int damageValue, float bulletStartX, float bulletStartY) {
    size_t entityId = createBaseEntity(engine, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
                                       twoDirections, posX, posY, velX, velY, dirX, dirY, hitboxHeight, hitboxWidth);

    auto healthComponent = std::make_shared<GameEngine::HealthComponent>(maxHealth);
    healthComponent->setComponentType(GameEngine::ComponentsType::getComponentType("HealthComponent"));
    auto damageComponent = std::make_shared<GameEngine::DamageComponent>(damageValue);
    damageComponent->setComponentType(GameEngine::ComponentsType::getComponentType("DamageComponent"));
    auto bulletStartPositionComponent =
        std::make_shared<GameEngine::BulletStartPositionComponent>(bulletStartX, bulletStartY);
    bulletStartPositionComponent->setComponentType(
        GameEngine::ComponentsType::getComponentType("BulletStartPositionComponent"));
    auto deathSpriteComponent =
        initDeathAnimation(deathSpriteSheetPath, deathFrames, deathSpriteSheetWidth, deathSpriteSheetHeight);

    engine.bindComponentToEntity(entityId, healthComponent);
    engine.bindComponentToEntity(entityId, damageComponent);
    engine.bindComponentToEntity(entityId, bulletStartPositionComponent);

    return entityId;
}

size_t EntityFactory::createBossMob(GameEngine::GameEngine& engine, const std::string& spriteSheetPath,
                                    int spriteSheetHeight, int spriteSheetWidth, int frames, bool twoDirections,
                                    const std::string& deathSpriteSheetPath, int deathSpriteSheetHeight,
                                    int deathSpriteSheetWidth, int deathFrames, float posX, float posY, float velX,
                                    float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight,
                                    int maxHealth, int damageValue, float bulletStartX, float bulletStartY,
                                    int stageValue) {
    size_t entityId = createBaseMob(engine, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames, twoDirections,
                                    deathSpriteSheetPath, deathSpriteSheetHeight, deathSpriteSheetWidth, deathFrames,
                                    posX, posY, velX, velY, dirX, dirY, hitboxWidth, hitboxHeight, maxHealth,
                                    damageValue, bulletStartX, bulletStartY);

    auto stageComponent = std::make_shared<GameEngine::BossStageComponent>(stageValue);
    stageComponent->setComponentType(GameEngine::ComponentsType::getComponentType("BossStageComponent"));

    engine.bindComponentToEntity(entityId, stageComponent);

    return entityId;
}

size_t EntityFactory::createPlayer(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int rectX,
                                   int rectY, int rectWidth, int rectHeight, float posX, float posY, float velX,
                                   float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight,
                                   int maxHealth, float bulletStartX, float bulletStartY) {
    size_t entityId = createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX,
                                       velY, dirX, dirY, hitboxWidth, hitboxHeight);

    auto healthComponent = std::make_shared<GameEngine::HealthComponent>(maxHealth);
    healthComponent->setComponentType(GameEngine::ComponentsType::getComponentType("HealthComponent"));
    auto bulletStartPositionComponent =
        std::make_shared<GameEngine::BulletStartPositionComponent>(bulletStartX, bulletStartY);
    bulletStartPositionComponent->setComponentType(
        GameEngine::ComponentsType::getComponentType("BulletStartPositionComponent"));

    engine.bindComponentToEntity(entityId, healthComponent);
    engine.bindComponentToEntity(entityId, bulletStartPositionComponent);

    return entityId;
}

size_t EntityFactory::createBullet(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int rectX,
                                   int rectY, int rectWidth, int rectHeight, float posX, float posY, float velX,
                                   float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight,
                                   int damageValue) {
    size_t entityId = createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX,
                                       velY, dirX, dirY, hitboxWidth, hitboxHeight);

    auto damageComponent = std::make_shared<GameEngine::DamageComponent>(damageValue);
    damageComponent->setComponentType(GameEngine::ComponentsType::getComponentType("DamageComponent"));

    engine.bindComponentToEntity(entityId, damageComponent);

    return entityId;
}

size_t EntityFactory::createPowerUp(GameEngine::GameEngine& engine, const std::string& spriteSheetPath, int rectX,
                                    int rectY, int rectWidth, int rectHeight, float posX, float posY, float velX,
                                    float velY, float dirX, float dirY, float hitboxWidth, float hitboxHeight) {
    return createBaseEntity(engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY, velX, velY, dirX,
                            dirY, hitboxWidth, hitboxHeight);
}

size_t EntityFactory::createBaseEntity(GameEngine::GameEngine& engine, const std::string& spriteSheetPath,
                                       int spriteSheetHeight, int spriteSheetWidth, int frames, bool twoDirections,
                                       float posX, float posY, float velX, float velY, float dirX, float dirY,
                                       float hitboxWidth, float hitboxHeight) {
    std::vector<std::optional<std::shared_ptr<GameEngine::IComponent>>> components;
    auto spriteComponent = initAnimation(spriteSheetPath, frames, spriteSheetWidth, spriteSheetHeight, twoDirections);

    auto positionComponent = std::make_shared<GameEngine::PositionComponent>(posX, posY);
    auto velocityComponent = std::make_shared<GameEngine::VelocityComponent>(velX, velY);
    auto directionComponent = std::make_shared<GameEngine::DirectionComponent>(dirX, dirY);
    auto hitboxComponent = std::make_shared<GameEngine::HitboxComponent>(hitboxWidth, hitboxHeight);
    auto collideComponent = std::make_shared<GameEngine::CollideComponent>();

    positionComponent->setComponentType(GameEngine::ComponentsType::getComponentType("PositionComponent"));
    velocityComponent->setComponentType(GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    directionComponent->setComponentType(GameEngine::ComponentsType::getComponentType("DirectionComponent"));
    hitboxComponent->setComponentType(GameEngine::ComponentsType::getComponentType("HitboxComponent"));
    collideComponent->setComponentType(GameEngine::ComponentsType::getComponentType("CollideComponent"));

    components.push_back(positionComponent);
    components.push_back(velocityComponent);
    components.push_back(directionComponent);
    components.push_back(hitboxComponent);
    components.push_back(collideComponent);
    components.push_back(spriteComponent);

    return engine.createEntity(components);
}

std::shared_ptr<GameEngine::SpriteAnimationComponent> EntityFactory::initAnimation(const std::string& spriteSheetPath,
                                                                                   int frames, int width, int height,
                                                                                   bool twoDirections) {
    auto spriteComponent = std::make_shared<GameEngine::SpriteAnimationComponent>();
    spriteComponent->setComponentType(GameEngine::ComponentsType::getComponentType("SpriteAnimationComponent"));

    spriteComponent->frameHeight = height;
    spriteComponent->frameWidth = static_cast<float>(width) / frames;
    spriteComponent->twoDirections = twoDirections;
    spriteComponent->frames = frames;
    int i = 0;

    for (i = 0; i < frames / 2; i++) {
        spriteComponent->spritePositionsLeft.push_back(Vec2f(i * static_cast<float>(width) / frames, 0));
    }
    for (; i < frames; i++) {
        if (!twoDirections) {
            spriteComponent->spritePositionsLeft.push_back(Vec2f(i * static_cast<float>(width) / frames, 0));
        } else {
            spriteComponent->spritePositionsRight.push_back(Vec2f(i * static_cast<float>(width) / frames, 0));
        }
    }

    return spriteComponent;
}

std::shared_ptr<GameEngine::DeathAnimationComponent>
EntityFactory::initDeathAnimation(const std::string& deathSpriteSheetPath, int deathFrames, int deathWidth,
                                  int deathHeight) {
    auto deathSpriteComponent = std::make_shared<GameEngine::DeathAnimationComponent>();
    deathSpriteComponent->setComponentType(GameEngine::ComponentsType::getComponentType("DeathAnimationComponent"));

    deathSpriteComponent->frameHeight = deathHeight;
    deathSpriteComponent->frameWidth = static_cast<float>(deathWidth) / deathFrames;
    deathSpriteComponent->frames = deathFrames;
    int i = 0;

    for (i = 0; i < deathFrames; i++) {
        deathSpriteComponent->spritePositions.push_back(Vec2f(i * static_cast<float>(deathWidth) / deathFrames, 0));
    }

    return deathSpriteComponent;
}
