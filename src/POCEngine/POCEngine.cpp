
#include "AComponent.hpp"
#include "ComponentContainer.hpp"
#include "test/EntityComponents.hpp"
#include "EntityFactory.hpp"
#include "test/EntitySystems.hpp"
#include "GameEngine.hpp"
#include "ISystem.hpp"
#include "RenderEngineSystem.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include <iostream>
#include "IsBullet.hpp"
#include "IsParallax.hpp"
#include "IsChargingBar.hpp"
#include "IsPlayer.hpp"

namespace GameEngine {


class ParallaxSystem : public ISystem {
public:
  ParallaxSystem() = default;

  ~ParallaxSystem() = default;

  void update(ComponentsContainer &componentsContainer,
              EventHandler &eventHandler) override {
    auto parallaxEntities = componentsContainer.getEntitiesWithComponent(
        ComponentsType::getNewComponentType("IsParallax"));
    Vect2 Velocity(0.0f, 0);

    for (auto entityID : parallaxEntities) {
      auto components = componentsContainer.getComponentsFromEntity(entityID);

      for (const auto &componentOpt : components) {
        if (!componentOpt)
          continue;
        if (componentOpt.value()->getComponentType() ==
            ComponentsType::getNewComponentType("VelocityComponent")) {
          auto velocityComponent = std::dynamic_pointer_cast<VelocityComponent>(
              componentOpt.value());

          if (velocityComponent) {
            velocityComponent->velocity = Velocity;
          }
        }
        if (componentOpt.value()->getComponentType() !=
            ComponentsType::getNewComponentType("IsParallax")) {
          auto spriteComponent =
              std::dynamic_pointer_cast<SpriteComponent>(componentOpt.value());

          if (spriteComponent) {
            Vect2 newPos =
                spriteComponent->pos -
                Vect2(0.1f * spriteComponent->layer + Velocity.x, 0);

            if (newPos.x + spriteComponent->rect1.w < 0) {
              newPos.x = 1920;
            }

            spriteComponent->pos = newPos;
          }
        }
      }
    }
  }
};

class MovementSystem : public ISystem {
public:
  void update(ComponentsContainer &componentsContainer,
              EventHandler &eventHandler) override {
    auto nbEntity = componentsContainer.getEntitiesWithComponent(
        ComponentsType::getNewComponentType("IsPlayer"));
    auto player = componentsContainer.getComponentsFromEntity(nbEntity[0]);
    auto event = eventHandler.getTriggeredEvent();
    std::shared_ptr<SpriteComponent> spriteComp;

    for (const auto &optComp : player) {
      if (optComp.has_value()) {
        auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
        if (aComp &&
            aComp->getComponentType() ==
                ComponentsType::getNewComponentType("SpriteComponent")) {
          spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
          if (spriteComp) {
            break;
          }
        }
      }
    }
    if (spriteComp) {
      Vect2 currentPosition = spriteComp->pos;
      if (event.first == "UP_KEY_PRESSED") {
        currentPosition.y -= 5;
      } else if (event.first == "DOWN_KEY_PRESSED") {
        currentPosition.y += 5;
      } else if (event.first == "LEFT_KEY_PRESSED") {
        currentPosition.x -= 5;
      } else if (event.first == "RIGHT_KEY_PRESSED") {
        currentPosition.x += 5;
      }
      spriteComp->pos = currentPosition;
    }
  }

private:
  bool done = false;
};

class ShootSystem : public ISystem {
public:
  void update(ComponentsContainer &componentsContainer,
              EventHandler &eventHandler) override {
    auto nbEntity = componentsContainer.getEntitiesWithComponent(
        ComponentsType::getNewComponentType("IsPlayer"));
    auto player = componentsContainer.getComponentsFromEntity(nbEntity[0]);
    auto event = eventHandler.getTriggeredEvent();
    std::shared_ptr<SpriteComponent> spriteComp;

    for (const auto &optComp : player) {
      if (optComp.has_value()) {
        auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
        if (aComp &&
            aComp->getComponentType() ==
                ComponentsType::getNewComponentType("SpriteComponent")) {
          spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
          if (spriteComp) {
            break;
          }
        }
      }
    }
    if (spriteComp) {
      std::cout << "SHOOT" << std::endl;
      Vect2 currentPosition = spriteComp->pos;
      std::cout << "Pos (x: " << spriteComp->pos.x
                << ",y: " << spriteComp->pos.y << ")" << std::endl;

      auto currentRect = spriteComp->rect1;
      auto spritePos = spriteComp->pos;

      Vect2 shootingPosition;
      shootingPosition.x = spritePos.x + currentRect.w;
      shootingPosition.y = spritePos.y + (currentRect.h) - 60;

      rect rect1;
      rect1.w = 125;
      rect1.h = 72;
      rect1.x = 0;
      rect1.y = 0;
      
      ColorR tint = {255,255,255,255};
      float scale = 1.0f;
      float rotation = 0.0f;
      
      auto bullet = componentsContainer.createEntity();
      std::cout << " New entitie id:" << bullet << std::endl;
      auto spriteComponent = std::make_shared<SpriteComponent>(
          "assets/11.png", shootingPosition, rect1, 4, scale, rotation, tint);
      auto PositionComponent = std::make_shared<PositionComponent2D>(
          Vect2(shootingPosition.x, shootingPosition.y));
      auto AABBComponent = std::make_shared<AABBComponent2D>(
        Vect2(shootingPosition.x, shootingPosition.y),
        Vect2(shootingPosition.x + rect1.w, shootingPosition.y + rect1.h));
      auto rectangleCollider = std::make_shared<RectangleColliderComponent2D>(rect1);
      componentsContainer.bindComponentToEntity(bullet, spriteComponent);
      auto isBulletComponent = std::make_shared<IsBullet>();
      componentsContainer.bindComponentToEntity(bullet, AABBComponent);
      componentsContainer.bindComponentToEntity(bullet, PositionComponent);
      componentsContainer.bindComponentToEntity(bullet, rectangleCollider);
      componentsContainer.bindComponentToEntity(bullet, isBulletComponent);
    }
  }

private:
  bool done = false;
};

class ChargingBar : public ISystem {
public:
  void update(ComponentsContainer &componentsContainer,
              EventHandler &eventHandler) override {
    auto events = eventHandler.getTriggeredEvent();
    if (events.first == "SPACE_KEY_PRESSED") {
      _charge += 1;
      if (_charge > _maxCharge) {
        _charge = _maxCharge;
      }
      auto entities = componentsContainer.getEntitiesWithComponent(
          ComponentsType::getNewComponentType("IsChargingBar"));
      for (auto entity : entities) {
        auto eses = componentsContainer.getComponentsFromEntity(entity);
        for (const auto &optComp : eses) {
          if (optComp.has_value()) {
            auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
            if (aComp &&
                aComp->getComponentType() ==
                    ComponentsType::getNewComponentType("SpriteComponent")) {
              auto spriteComp =
                  std::dynamic_pointer_cast<SpriteComponent>(aComp);
              if (spriteComp) {
                auto currentRect = spriteComp->rect1;
                currentRect.w = _charge * 2;
                std::cout << "CURRENT RECT: " << currentRect.w << std::endl;
                spriteComp->rect1 = currentRect;
                std::cout << "UPDATED: " << _charge << std::endl;
              }
            }
          }
        }
      }
    } else if (events.first == "SPACE_KEY_RELEASED") {
      _charge -= 4;
      if (_charge < 0) {
        _charge = 0;
        eventHandler.queueEvent("STOP_UNCHARGING");
      }
      auto entities = componentsContainer.getEntitiesWithComponent(
          ComponentsType::getNewComponentType("IsChargingBar"));
      for (auto entity : entities) {
        auto eses = componentsContainer.getComponentsFromEntity(entity);
        for (const auto &optComp : eses) {
          if (optComp.has_value()) {
            auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
            if (aComp &&
                aComp->getComponentType() ==
                    ComponentsType::getNewComponentType("SpriteComponent")) {
              auto spriteComp =
                  std::dynamic_pointer_cast<SpriteComponent>(aComp);
              if (spriteComp) {
                auto currentRect = spriteComp->rect1;
                currentRect.w = _charge * 2;
                spriteComp->rect1 = currentRect;
              }
            }
          }
        }
      }
    }
  }

private:
  int _charge = 0;
  int _maxCharge = 103;
};

class MovementBulletSystem : public ISystem {
public:
  void update(ComponentsContainer &componentsContainer,
              EventHandler &eventHandler) override {
    auto entities = componentsContainer.getEntitiesWithComponent(
        ComponentsType::getNewComponentType("IsBullet"));
    for (const auto &entity : entities) {
      auto eses = componentsContainer.getComponentsFromEntity(entity);
      auto event = eventHandler.getTriggeredEvent();
      std::shared_ptr<SpriteComponent> spriteComp;
      std::shared_ptr<IsBullet> bulletComp;
      std::shared_ptr<PositionComponent2D> positionComp;
      std::shared_ptr<AABBComponent2D> aabbComp;

      for (const auto &optComp : eses) {
        if (optComp.has_value()) {
          auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
          if (aComp &&
              aComp->getComponentType() ==
                  ComponentsType::getNewComponentType("SpriteComponent")) {
            spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
          }
          if (aComp &&
              aComp->getComponentType() ==
                  ComponentsType::getNewComponentType("BulletComponent")) {
            bulletComp = std::dynamic_pointer_cast<IsBullet>(aComp);
          }
          if (aComp &&
              aComp->getComponentType() ==
                  ComponentsType::getNewComponentType("PositionComponent2D")) {
            positionComp = std::dynamic_pointer_cast<PositionComponent2D>(aComp);
          }
          if (aComp &&
              aComp->getComponentType() ==
                  ComponentsType::getNewComponentType("AABBComponent2D")) {
            aabbComp = std::dynamic_pointer_cast<AABBComponent2D>(aComp);
          }
        }
      }
      if (spriteComp && bulletComp) {
        auto pos = spriteComp->pos;
        //auto speed = bulletComp.speed;
        auto speed = 5;
        auto rect = spriteComp->rect1;
        positionComp->pos= {pos.x + speed, pos.y};
        aabbComp->minExtents = {pos.x + speed, pos.y};
        aabbComp->maxExtents = {pos.x + rect.w + speed, pos.y + rect.h};
        spriteComp->pos = {pos.x + speed, pos.y};
      }
    }
  }

private:
  bool done = false;
};
} // namespace GameEngine

void spawnMob(GameEngine::GameEngine &engine) {
  // random number between 50 and 1000
  int randomY = rand() % 950 + 50;
  size_t id =
      EntityFactory::getInstance().spawnCancerMob(engine, 1500, randomY, -1, 0);
}

int main() {
  GameEngine::GameEngine engine;

  auto collision = std::make_shared<GameEngine::PhysicsEngineCollisionSystem2D>();
  auto paralax = std::make_shared<GameEngine::ParallaxSystem>();
  auto move = std::make_shared<GameEngine::MovementSystem>();
  auto shoot = std::make_shared<GameEngine::ShootSystem>();
  auto moveShoot = std::make_shared<GameEngine::MovementBulletSystem>();

  GameEngine::rect rect2(0, 0, 1920, 1080);
  GameEngine::Vect2 pos2(0, 0);
  GameEngine::Vect2 pos3(1920, 0);
  
     GameEngine::ColorR tint = {255,255,255,255};
    float scale = 1.0f;
    float rotation = 0.0f;

  auto paralaxEntity = engine.createEntity();
  auto isParalaxComponent = std::make_shared<IsParallax>();
  engine.bindComponentToEntity(paralaxEntity, isParalaxComponent);
  auto velocityComponent = std::make_shared<GameEngine::VelocityComponent>(
      GameEngine::Vect2(1.0f, 0.0f));
  engine.bindComponentToEntity(paralaxEntity, velocityComponent);
  auto spritecompoennt2 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/background_1.png", pos2, rect2, 2, scale, rotation, tint);
  engine.bindComponentToEntity(paralaxEntity, spritecompoennt2);

  auto paralaxEntity2 = engine.createEntity();
  auto isParalaxComponent1 =
      std::make_shared<IsParallax>();
  engine.bindComponentToEntity(paralaxEntity2, isParalaxComponent1);
  auto spritecompoennt3 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/background_1.png", pos3, rect2, 2, scale, rotation, tint);
  engine.bindComponentToEntity(paralaxEntity2, spritecompoennt3);

  auto paralaxEntity3 = engine.createEntity();
  auto isParalaxComponent2 =
      std::make_shared<IsParallax>();
  engine.bindComponentToEntity(paralaxEntity3, isParalaxComponent2);
  auto spritecompoennt4 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/Planets/Planet_Furnace_01_560x560.png",
      GameEngine::Vect2(300, 300), GameEngine::rect(0, 0, 560, 560), 3, scale, rotation, tint);
  engine.bindComponentToEntity(paralaxEntity3, spritecompoennt4);

  engine.addSystem("CollisionSystem", collision);
  engine.addSystem("ParallaxSystem", paralax);
  engine.addSystem("RenderEngineSystem",
                   std::make_shared<GameEngine::RenderEngineSystem>(
                       1920, 1080, "POC Engine"));
  engine.addEvent("UP_KEY_PRESSED", move);
  engine.setContinuousEvent("UP_KEY_PRESSED", "UP_KEY_RELEASED");
  engine.addEvent("DOWN_KEY_PRESSED", move);
  engine.setContinuousEvent("DOWN_KEY_PRESSED", "DOWN_KEY_RELEASED");
  engine.addEvent("LEFT_KEY_PRESSED", move);
  engine.setContinuousEvent("LEFT_KEY_PRESSED", "LEFT_KEY_RELEASED");
  engine.addEvent("RIGHT_KEY_PRESSED", move);
  engine.setContinuousEvent("RIGHT_KEY_PRESSED", "RIGHT_KEY_RELEASED");

  engine.addEvent("ShootSystem", shoot);
  engine.scheduleEvent("ShootSystem", 50);
  engine.addEvent("MovementShoot", moveShoot);
  engine.scheduleEvent("MovementShoot", 1);

  engine.setContinuousEvent("SPACE_KEY_PRESSED", "SPACE_KEY_RELEASED");

  engine.setContinuousEvent("SPACE_KEY_RELEASED", "STOP_UNCHARGING");
  auto chargingBarEntityLayer1 = engine.createEntity();
  auto isChargingBarComponent = std::make_shared<IsChargingBar>();
  engine.bindComponentToEntity(chargingBarEntityLayer1, isChargingBarComponent);
  auto spritecompoennt5 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/HUD/BlueBar.png", GameEngine::Vect2(0, 0),
      GameEngine::rect(0, 0, 0, 26), 100, scale, rotation, tint);
  engine.bindComponentToEntity(chargingBarEntityLayer1, spritecompoennt5);

  auto chargingBarEntityLayer2 = engine.createEntity();
  auto spritecompoennt6 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/HUD/EmptyBar.png", GameEngine::Vect2(0, 0),
      GameEngine::rect(0, 0, 208, 26), 99, scale, rotation, tint);
  engine.bindComponentToEntity(chargingBarEntityLayer2, spritecompoennt6);

  auto chargingBar = std::make_shared<GameEngine::ChargingBar>();

  engine.addEvent("SPACE_KEY_PRESSED", chargingBar);
  engine.addEvent("SPACE_KEY_RELEASED", chargingBar);

  GameEngine::Vect2 pos;
  pos.x = 100;
  pos.y = 100;

  GameEngine::rect rect1;
  rect1.w = 144;
  rect1.h = 59;
  rect1.x = 0;
  rect1.y = 0;
  GameEngine::ColorR color;
  color.r = 0;
  color.g = 0;
  color.b = 255;
  color.a = 255;

  auto textEntity = engine.createEntity();

  auto Player = engine.createEntity();
  auto spritecompoennt = std::make_shared<GameEngine::SpriteComponent>(
      "assets/spaceship.png", pos, rect1, 4, scale, rotation, tint);
  engine.bindComponentToEntity(Player, spritecompoennt);
  auto isPLayerComponent = std::make_shared<IsPlayer>();
  engine.bindComponentToEntity(Player, isPLayerComponent);

  auto updateSprite = std::make_shared<GameEngine::updateEntitySpriteSystem>();
  auto moveEntities = std::make_shared<GameEngine::updatePositionSystem>();
  engine.addSystem("updatePositionSystem", moveEntities);
  engine.addEvent("UpdateAnimation", updateSprite);
  std::cout << "spawnMob1" << std::endl;
  //   engine.addEvent("SpawnMob", [&engine]() { spawnMob(engine); });
  engine.scheduleEvent("UpdateAnimation", 30);
  //   engine.scheduleEvent("SpawnMob", 1000);

  for (int i = 0; i < 5; i++) {
    size_t id = EntityFactory::getInstance().spawnCancerMob(
        engine, 1980, 200 + i * 150, -1, 0);
  }

  engine.run();
  return 0;
}