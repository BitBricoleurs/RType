/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SyncChargeAnimations
*/

#include "ISystem.hpp"
#include "PositionComponent2D.hpp"
#include "IsStarship.hpp"
#include "Shooter.hpp"
#include "IsPlayer.hpp"

namespace Client {
    class SyncChargeAnimations : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
        private:
            void updateAnimationPos(size_t chargeAnimationID, size_t playerID, GameEngine::ComponentsContainer &componentsContainer);
    };

}

