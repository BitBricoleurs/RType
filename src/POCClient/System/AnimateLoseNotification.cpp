//
// Created by Clément Lagasse on 03/11/2023.
//

#include "AnimateLoseNotification.hpp"

void Client::AnimateLoseNotification::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto SpriteCompType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
    auto PlayNotifAnimType = GameEngine::ComponentsType::getComponentType("LoseNotifAnimation");

    auto playnotifMay = componentsContainer.getEntityWithUniqueComponent(PlayNotifAnimType);

    auto playCompMay = componentsContainer.getComponent(playnotifMay, PlayNotifAnimType);
    if (!playCompMay.has_value())
        return;

    auto playComp = std::static_pointer_cast<Client::LoseNotifAnimation>(playCompMay.value());
    // If First call then start animation
    if (playComp->currentImagesIndex == -1) {
        componentsContainer.bindComponentToEntity(playnotifMay, playComp->spriteComponents[0]);
        playComp->currentImagesIndex = 0;
        playComp->spriteComponents[0]->isVisible = true;
        playComp->state = Client::LoseNotifAnimation::AnimationState::FRAME1;
        return;
    }
    playComp->currentFrameIndex++;
    // if last frame of image
    if (playComp->currentFrameIndex > playComp->nbrFramePerImages[playComp->currentImagesIndex] - 1) {
        // if last image of last frame
        if (playComp->state == Client::LoseNotifAnimation::AnimationState::FRAME4) {
            eventHandler.unscheduleEvent("START_NOTIF_LOSE");
            return;
        }
        // if not the last image of last frame
        playComp->state = static_cast<Client::LoseNotifAnimation::AnimationState>(playComp->state + 1);
        playComp->currentFrameIndex = 0;
        playComp->spriteComponents[playComp->currentImagesIndex]->isVisible = false;
        playComp->currentImagesIndex++;
        componentsContainer.bindComponentToEntity(playnotifMay, playComp->spriteComponents[playComp->currentImagesIndex]);
        playComp->spriteComponents[playComp->currentImagesIndex]->isVisible = true;
        playComp->spriteComponents[playComp->currentImagesIndex]->rect1.x = 0;
        return;
    }
    // Update rect of image to display
    playComp->spriteComponents[playComp->currentImagesIndex]->rect1.x += playComp->spriteSheetSize[playComp->currentImagesIndex].x / playComp->nbrFramePerImages[playComp->currentImagesIndex];
}