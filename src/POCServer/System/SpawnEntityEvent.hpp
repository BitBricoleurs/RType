//
// Created by clagasse on 11/1/23.
//


#pragma once

#include "SpawnEntity.hpp"

namespace Server {

    class SpawnEntityChangeLevel : public GameEngine::ISystem {
        public:
        SpawnEntityChangeLevel(std::shared_ptr<Server::SpawnEntity> &spawnEntity): spawnEntity(spawnEntity) {};
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

        private:
        std::shared_ptr<Server::SpawnEntity> spawnEntity;
    };

    class SpawnEntityResetLevel : public GameEngine::ISystem {
        public:
        SpawnEntityResetLevel(std::shared_ptr<Server::SpawnEntity> &spawnEntity): spawnEntity(spawnEntity) {};
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

        private:
        std::shared_ptr<Server::SpawnEntity> spawnEntity;
    };
}
