/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AnimateDeath
*/

#include "AnimateDeath.hpp"

namespace Client {

    void AnimateDeath::update(GameEngine::ComponentsContainer &componentsContainer,
                              GameEngine::EventHandler &eventHandler) {

        size_t entityID = 0;
        try {
            entityID =
                    std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
        } catch (std::bad_any_cast &e) {
            return;
        };
      auto deathOpt = componentsContainer.getComponent(
          entityID, GameEngine::ComponentsType::getComponentType("DeathAnimation"));
      auto spriteOpt = componentsContainer.getComponent(
          entityID,
          GameEngine::ComponentsType::getComponentType("SpriteComponent"));

      if (deathOpt.has_value() && spriteOpt.has_value()) {
        auto sprite = std::dynamic_pointer_cast<RenderEngine::SpriteComponent>(
            spriteOpt.value());
        auto deathAnim =
            std::dynamic_pointer_cast<DeathAnimation>(deathOpt.value());
        if (sprite->imagePath != deathAnim->filepath) {
          sprite->rect1.w = deathAnim->frameWidth;
          sprite->rect1.h = deathAnim->frameHeight;
          sprite->imagePath = deathAnim->filepath;
          componentsContainer.unbindComponentFromEntity(
              entityID,
              GameEngine::ComponentsType::getComponentType("AColliderComponent2D"));
        }
        if (deathAnim->currentFrameIndex == deathAnim->frames) {
            EntityFactory &factory = EntityFactory::getInstance();
          factory.unregisterEntity(entityID);
          componentsContainer.deleteEntity(entityID);
          eventHandler.unscheduleEvent("MobDeath", entityID);
          return;
        }
        deathAnim->currentFrame =
            deathAnim->spritePositions[deathAnim->currentFrameIndex++];
        sprite->rect1.x = deathAnim->currentFrame.x;
        sprite->rect1.y = deathAnim->currentFrame.y;
      }
    }

}