/*
** EPITECH PROJECT, 2023
** RType
** File description:
** UpdateBugSprite
*/

#include "UpdateBugSprite.hpp"
#include <memory>

namespace Client {
    void UpdateBugSprite::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        try {
            size_t bugId = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

            auto bugSpriteCollectionOpt = componentsContainer.getComponent(bugId, GameEngine::ComponentsType::getComponentType("SpriteAnimation"));
            auto bugVelocityOpt = componentsContainer.getComponent(bugId, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
            auto bugSpriteOpt = componentsContainer.getComponent(bugId, GameEngine::ComponentsType::getComponentType("SpriteComponent"));

            if (!bugSpriteCollectionOpt.has_value() || !bugVelocityOpt.has_value() || !bugSpriteOpt.has_value())
                return;

            auto bugSpriteCollection = std::static_pointer_cast<SpriteAnimation>(bugSpriteCollectionOpt.value());
            auto bugVelocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(bugVelocityOpt.value());
            auto bugSprite = std::static_pointer_cast<RenderEngine::SpriteComponent>(bugSpriteOpt.value());

            if (bugVelocity->velocity.x == 0 && bugVelocity->velocity.y == 0) {
                return; // Error case: velocity is zero, no direction
            }

            // Calculate the angle of the velocity vector
            double angle = std::atan2(bugVelocity->velocity.y, bugVelocity->velocity.x); // Returns a value [-PI, PI]
            angle = angle * (180.0 / M_PI); // Convert to degrees

             // Normalize angle to [0, 360)
            if (angle < 0) {
                angle += 360;
            }

            // Calculate frame index
            int frames = 16;
            double anglePerFrame = 360.0 / frames;
            int frameIndex = static_cast<int>(angle / anglePerFrame);

            bugSpriteCollection->currentFrameIndex = frameIndex;
            bugSpriteCollection->currentFrame = bugSpriteCollection->spritePositionsLeft[bugSpriteCollection->currentFrameIndex];

            // Set the sprite
            bugSprite->rect1.x = bugSpriteCollection->currentFrame.x;
            bugSprite->rect1.y = bugSpriteCollection->currentFrame.y;

        } catch (std::bad_any_cast &e) {
            std::cerr << "Error in UpdateBugSprite: " << e.what() << std::endl;
            return;
        }
    }
}