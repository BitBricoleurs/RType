/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BossHit
*/

#include "BossHit.hpp"
#include <cstddef>


namespace Server {

    void BossHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        try {
            auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
            auto firstEntityOptBoss = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsBoss"));

            size_t bossId = firstEntity;
            size_t bulletId = secondEntity;
            if (!firstEntityOptBoss.has_value()) {
                bossId = secondEntity;
                bulletId = firstEntity;
            }

            auto hpComponent = componentsContainer.getComponent(bossId, GameEngine::ComponentsType::getComponentType("Health"));
            if (!hpComponent.has_value())
                return;
            auto hpComponentCast = std::static_pointer_cast<Health>(hpComponent.value());

            auto DamageBullet = componentsContainer.getComponent(bulletId, GameEngine::ComponentsType::getComponentType("Damage"));
            if (!DamageBullet.has_value())
                return;
            auto DamageBulletCast = std::dynamic_pointer_cast<Damage>(*DamageBullet);

            if (DamageBulletCast != nullptr)
                hpComponentCast->currentHealth -= DamageBulletCast->damageValue;

            if (hpComponentCast->currentHealth <= 0) {
                std::vector<size_t> idsBullet = {bulletId};
                killBossNetwork(eventHandler, idsBullet);
                componentsContainer.deleteEntity(bossId);
            }
            componentsContainer.deleteEntity(bulletId);
        } catch (std::exception &e) {
            std::cout << "Error in BossHit : " << e.what() << std::endl;
        }
    }

    void BossHit::killBossNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill)
    {
         std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", entitiesToKill, "", std::vector<std::any>{});
         std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
         eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }

}