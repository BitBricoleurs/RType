//
// Created by Clément Lagasse on 03/11/2023.
//

#include "ClearAnimateLoseNotification.hpp"

void Client::ClearAnimateLoseNotification::update(GameEngine::ComponentsContainer &componentsContainer,
                                                   GameEngine::EventHandler &eventHandler) {
    auto SpriteCompType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
    auto PlayNotifAnimType = GameEngine::ComponentsType::getComponentType("LoseNotifAnimation");

    auto playnotifMay = componentsContainer.getEntityWithUniqueComponent(PlayNotifAnimType);

    auto playCompMay = componentsContainer.getComponent(playnotifMay, PlayNotifAnimType);
    auto spriteCompMay = componentsContainer.getComponent(playnotifMay, SpriteCompType);
    if (!playCompMay.has_value() || !spriteCompMay.has_value())
        return;

    auto playComp = std::static_pointer_cast<Client::LoseNotifAnimation>(playCompMay.value());
    auto spriteComp = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteCompMay.value());
    playComp->state = Client::LoseNotifAnimation::AnimationState::HIDE;

    eventHandler.unscheduleEvent("START_NOTIF_LOSE");
    if (spriteComp->isVisible) {
        spriteComp->isVisible = false;
    }
    spriteComp->rect1.x = 0;
    playComp->currentFrameIndex = 0;
    playComp->currentImagesIndex = -1;
    componentsContainer.unbindComponentFromEntity(playnotifMay, SpriteCompType);
}
