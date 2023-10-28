/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Mob
*/

#include "EntityFactory.hpp"
#include <memory>

namespace Server {

    size_t EntityFactory::createBaseMob(
        GameEngine::ComponentsContainer &container,
        int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
        Utils::Vect2 velocity, int maxHealth, int damageValue, float scale) {
      size_t entityId = createBaseEntity(
          container, hitboxHeight, hitboxWidth, pos, velocity, scale);

      auto healthComponent = std::make_shared<Health>(maxHealth);
      auto damageComponent = std::make_shared<Damage>(damageValue);
      auto mobComponent = std::make_shared<IsMob>();

      container.bindComponentToEntity(entityId, healthComponent);
      container.bindComponentToEntity(entityId, damageComponent);
      container.bindComponentToEntity(entityId, mobComponent);

      return entityId;
    }

    size_t EntityFactory::createBossMob(
        GameEngine::ComponentsContainer &container, int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
        Utils::Vect2 velocity, int maxHealth, int damageValue, int stageValue,
        float scale) {

      size_t entityId = createBaseMob(container, hitboxHeight, hitboxWidth, pos, velocity, maxHealth, damageValue,scale);

      auto stageComponent = std::make_shared<BossStage>(stageValue);
      auto bossComponent = std::make_shared<IsBoss>();

      container.unbindComponentFromEntity(
          entityId, GameEngine::ComponentsType::getComponentType("Mob"));
      container.bindComponentToEntity(entityId, bossComponent);
      container.bindComponentToEntity(entityId, stageComponent);

      return entityId;
    }

    size_t EntityFactory::createPlayer(GameEngine::ComponentsContainer &container,
                                       int hitboxHeight, int hitboxWidth,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity, int maxHealth,
                                       int damageValue, int bulletStartX, int bulletStartY, float scale, size_t entityCharge,
                                       Utils::Vect2 bulletVelocity, int typeBullet) {
      size_t entityId = createBaseEntity(
          container, hitboxHeight, hitboxWidth,
          pos, velocity, scale);

      auto healthComponent = std::make_shared<Health>(maxHealth);
      auto shooterComp = std::make_shared<Shooter>(Utils::Vect2(bulletStartX, bulletStartY), bulletVelocity, typeBullet);
      auto playerComponent = std::make_shared<IsPlayer>(entityCharge);

      container.bindComponentToEntity(entityId, healthComponent);
      container.bindComponentToEntity(entityId, playerComponent);
      container.bindComponentToEntity(entityId, shooterComp);

      return entityId;
    }

    size_t EntityFactory::createBullet(GameEngine::ComponentsContainer &container,
                                       int hitboxHeight, int hitboxWidth,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity, int damageValue,
                                       bool isPlayerBullet, float scale) {
      size_t entityId = createBaseEntity(
          container, hitboxHeight, hitboxWidth,
          pos, velocity, scale);

      auto damageComponent = std::make_shared<Damage>(damageValue);
      auto bulletComponent = std::make_shared<IsBullet>(isPlayerBullet);
      container.bindComponentToEntity(entityId, damageComponent);
      container.bindComponentToEntity(entityId, bulletComponent);

      return entityId;
    }

    size_t EntityFactory::createPowerUp(GameEngine::ComponentsContainer &container,
                                        int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
                                        Utils::Vect2 velocity, int playerA, float scale) {
      size_t entityId = createBaseEntity(container, hitboxHeight, hitboxWidth, pos,
                                         velocity, scale);
      auto powerUpComponent = std::make_shared<IsPowerUp>();
      container.bindComponentToEntity(entityId, powerUpComponent);
      return entityId;
    }

    size_t EntityFactory::createChargeAnimation(
        GameEngine::ComponentsContainer &container, Utils::Vect2 pos, Utils::Vect2 velocity) {

      auto positionComponent = std::make_shared<PhysicsEngine::PositionComponent2D>(pos);
      auto movementComp = std::make_shared<PhysicsEngine::MovementComponent>();
      auto velocityComponent = std::make_shared<PhysicsEngine::VelocityComponent>(velocity);


      size_t animationId = container.createEntity();
      container.bindComponentToEntity(animationId, positionComponent);
      container.bindComponentToEntity(animationId, velocityComponent);
      container.bindComponentToEntity(animationId, movementComp);
      return animationId;
    }

    size_t EntityFactory::createBaseEntity(
        GameEngine::ComponentsContainer &container,
        int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
        Utils::Vect2 velocity, float scale) {

      auto movementComponent = std::make_shared<PhysicsEngine::MovementComponent>();
      auto positionComponent = std::make_shared<PhysicsEngine::PositionComponent2D>(pos);
      auto velocityComponent = std::make_shared<PhysicsEngine::VelocityComponent>(velocity);

      auto AABBComponent = std::make_shared<PhysicsEngine::AABBComponent2D>(pos, Utils::Vect2(pos.x + hitboxWidth * scale, pos.y + hitboxHeight * scale));
      auto rectangleCollider = std::make_shared<PhysicsEngine::RectangleColliderComponent2D>(Utils::rect(0, 0, hitboxWidth * scale, hitboxHeight * scale));


      size_t entityId = container.createEntity();

      container.bindComponentToEntity(entityId, positionComponent);
      container.bindComponentToEntity(entityId, velocityComponent);
      container.bindComponentToEntity(entityId, movementComponent);
      container.bindComponentToEntity(entityId, AABBComponent);
      container.bindComponentToEntity(entityId, rectangleCollider);

      return entityId;
    }

    void EntityFactory::updateEntityNetwork(GameEngine::EventHandler &eventHandler, size_t entityId, Utils::Vect2 &pos, Utils::Vect2 &velocity)
    {
        std::vector<size_t> ids = {entityId};
        std::vector<std::any> args = {};
        args.push_back(pos.x);
        args.push_back(pos.y);
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
        std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
        args.clear();
        args.push_back(velocity.x);
        args.push_back(velocity.y);
        message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
        allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
    }

    void EntityFactory::updateEntityNetworkWithPos(GameEngine::EventHandler &eventHandler, size_t entityId, Utils::Vect2 &pos)
    {
        std::vector<size_t> ids = {entityId};
        std::vector<std::any> args = {};
        args.push_back(pos.x);
        args.push_back(pos.y);
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
        std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
    }

    void EntityFactory::updateEntityNetworkWithVelocity(GameEngine::EventHandler &eventHandler, size_t entityId, Utils::Vect2 &velocity)
    {
        std::vector<size_t> ids = {entityId};
        std::vector<std::any> args = {};
        args.push_back(velocity.x);
        args.push_back(velocity.y);
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
         std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
    }
}
