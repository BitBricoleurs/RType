/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnEntity
*/

#include "SpawnEntity.hpp"

namespace Server {

    SpawnEntity::SpawnEntity(std::string path) : directoryPath(std::move(path)), currentMapContent(nlohmann::json::object())
    {
        loadMapFiles(directoryPath);
        if (!mapFiles.empty()) {
            loadMap(mapFiles[mapIndex]);
        }
    }

    void SpawnEntity::changeLevel() {
        if (mapIndex + 1 < mapFiles.size()) {
            mapIndex++;
            loadMap(mapFiles[mapIndex]);
            currentTick = 0;
        } else {
            mapIndex = 0;
            loadMap(mapFiles[mapIndex]);
            currentTick = 0;
        }
    }

    void SpawnEntity::resetCurrentLevel() {
        loadMap(mapFiles[mapIndex]);
        currentTick = 0;
    }

    void SpawnEntity::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        auto compTypeGameState = GameEngine::ComponentsType::getComponentType("GameState");
        size_t gameStateEntity = componentsContainer.getEntityWithUniqueComponent(compTypeGameState);
        auto compMay = componentsContainer.getComponent(gameStateEntity, compTypeGameState);
        if (!compMay.has_value())
            return;
        auto gameStateComp = std::static_pointer_cast<Utils::GameState>(compMay.value());
        if (gameStateComp->_state != Utils::GameState::State::RUNNING)
            return;
        currentTick++;
        int mobsSize = currentMapContent.getSize("/mobs");
        if (currentMapContent.keyExists("/winCondition/tick")) {
            int winTick = currentMapContent.getInt("/winCondition/tick");
            if (currentTick >= winTick) {
                winLevel(eventHandler);
                return;
            };
        }
        auto entityId = 0;
        for (int i = 0; i < mobsSize; i++) {
            int tick = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/tick");

            if (currentTick == tick) {
                int posX = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/position/x");
                int posY = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/position/y");
                Utils::Vect2 position(static_cast<float>(posX), static_cast<float>(posY));

                float velocityX = currentMapContent.getFloat("/mobs/" + std::to_string(i) + "/velocity/x");
                float velocityY = currentMapContent.getFloat("/mobs/" + std::to_string(i) + "/velocity/y");
                Utils::Vect2 velocity(velocityX, velocityY);

                bool dropPowerup = currentMapContent.getBool("/mobs/" + std::to_string(i) + "/dropPowerUp");
                std::string mobType = currentMapContent.getString("/mobs/" + std::to_string(i) + "/mobType");
                bool isLastMob = currentMapContent.getBool("/mobs/" + std::to_string(i) + "/isLastMob");

                if (mobType == "cancerMob") {
                    entityId = EntityFactory::getInstance().spawnCancerMob(componentsContainer, eventHandler, position, velocity, dropPowerup);
                } else if (mobType == "pataPataMob") {
                    entityId = EntityFactory::getInstance().spawnPataPataMob(componentsContainer, eventHandler, position, velocity, dropPowerup);
                } else if (mobType == "bellmite") {
                     entityId = EntityFactory::getInstance().createBellmite(componentsContainer, eventHandler, position, velocity, dropPowerup);
                } else if (mobType == "bugMob") {
                    entityId= EntityFactory::getInstance().spawnBugMob(componentsContainer, eventHandler, position, velocity, dropPowerup);
                } else if (mobType == "bugGroup") {
                    entityId= EntityFactory::getInstance().spawnBugGroup(componentsContainer, eventHandler, position, velocity, dropPowerup);
                }
                if (isLastMob) {
                    std::cout << "isLastMob" << std::endl;
                    componentsContainer.bindComponentToEntity(entityId, std::make_shared<IsLastMob>());
                }
            }
        }
        int parallaxSize = currentMapContent.getSize("/parallax");
        for (int i = 0; i < parallaxSize; i++) {
            int tick = currentMapContent.getInt("/parallax/" + std::to_string(i) + "/tick");
            if (currentTick == tick) {
                int posX = currentMapContent.getInt("/parallax/" + std::to_string(i) + "/position/x");
                int posY = currentMapContent.getInt("/parallax/" + std::to_string(i) + "/position/y");
                int layer = currentMapContent.getInt("/parallax/" + std::to_string(i) + "/layer");
                bool isLooping = currentMapContent.getBool("/parallax/" + std::to_string(i) + "/isLooping");
                float speed = currentMapContent.getFloat("/parallax/" + std::to_string(i) + "/velocity/x");
                Utils::Vect2 position(static_cast<float>(posX), static_cast<float>(posY));
                ParallaxType type = static_cast<ParallaxType>(currentMapContent.getInt("/parallax/" + std::to_string(i) + "/type"));
                EntityFactory::getInstance().spawnParallax(componentsContainer, eventHandler, position, speed, layer, type, isLooping);
            }
        }
    }


    void SpawnEntity::loadMapFiles(const std::string &path)
    {
        std::string newPath = LoadConfig::LoadConfig::getInstance().getExecutablePath();
            newPath = newPath + path;
        for (const auto &entry : std::filesystem::directory_iterator(newPath)) {
            if (entry.path().extension() == ".json") {
                mapFiles.push_back(entry.path().string());
            }
        }
        std::sort(mapFiles.begin(), mapFiles.end());
    }

    bool SpawnEntity::loadMap(const std::string &filePath)
    {
        try {
            currentMapContent = LoadConfig::LoadConfig::getInstance().loadConfigWithoutPath(filePath);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error loading map: " << e.what() << std::endl;
            return false;
        }
    }

    void SpawnEntity::winLevel(GameEngine::EventHandler &eventHandler)
    {
        eventHandler.queueEvent("WIN_LEVEL");
        std::cout << "Level won" << std::endl;
    }
}
