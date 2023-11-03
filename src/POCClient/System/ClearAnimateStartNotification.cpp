//
// Created by Clément Lagasse on 03/11/2023.
//

#include "ClearAnimateStartNotification.hpp"

void Client::ClearAnimateStartNotification::update(GameEngine::ComponentsContainer &componentsContainer,
                                                   GameEngine::EventHandler &eventHandler) {
    auto SpriteCompType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
    auto PlayNotifAnimType = GameEngine::ComponentsType::getComponentType("PlayNotifAnimation");

    auto playnotifMay = componentsContainer.getEntityWithUniqueComponent(PlayNotifAnimType);

    auto playCompMay = componentsContainer.getComponent(playnotifMay, PlayNotifAnimType);
    auto spriteCompMay = componentsContainer.getComponent(playnotifMay, SpriteCompType);
    if (!playCompMay.has_value() || !spriteCompMay.has_value())
        return;

    auto playComp = std::static_pointer_cast<Client::PlayNotifAnimation>(playCompMay.value());
    auto spriteComp = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteCompMay.value());
    playComp->state = Client::PlayNotifAnimation::AnimationState::HIDE;

    eventHandler.unscheduleEvent("PLAY_NOTIF_START_GAME");
    if (spriteComp->isVisible) {
        spriteComp->isVisible = false;
    }
    spriteComp->rect1.x = 0;
    playComp->currentFrameIndex = 0;
}
