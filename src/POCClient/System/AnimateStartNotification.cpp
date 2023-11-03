//
// Created by Clément Lagasse on 03/11/2023.
//

#include "AnimateStartNotification.hpp"

void Client::AnimateStartNotification::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto SpriteCompType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
    auto PlayNotifAnimType = GameEngine::ComponentsType::getComponentType("PlayNotifAnimation");

    auto playnotifMay = componentsContainer.getEntityWithUniqueComponent(PlayNotifAnimType);

    auto playCompMay = componentsContainer.getComponent(playnotifMay, PlayNotifAnimType);
    auto spriteCompMay = componentsContainer.getComponent(playnotifMay, SpriteCompType);
    if (!playCompMay.has_value() || !spriteCompMay.has_value())
        return;

    auto playComp = std::static_pointer_cast<Client::PlayNotifAnimation>(playCompMay.value());
    auto spriteComp = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteCompMay.value());
    if (playComp->state == Client::PlayNotifAnimation::AnimationState::PRESSED)
        return;
    if (playComp->state == Client::PlayNotifAnimation::AnimationState::HIDE)
        playComp->state = Client::PlayNotifAnimation::AnimationState::SHOW;

    if (playComp->frames == playComp->currentFrameIndex) {
        eventHandler.unscheduleEvent("PLAY_NOTIF_START_GAME");
    }
    if (!spriteComp->isVisible) {
        spriteComp->isVisible = true;
    }
    spriteComp->rect1.x += playComp->frameWidth;
    playComp->currentFrameIndex++;
}