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
        for (int i = 0; i < mobsSize;) {
            int tick = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/tick");

            if (currentTick == tick) {
                float posX = currentMapContent.getFloat("/mobs/" + std::to_string(i) + "/position/x");
                float posY = currentMapContent.getFloat("/mobs/" + std::to_string(i) + "/position/y");
                Utils::Vect2 position(posX, posY);

                bool dropPowerup = currentMapContent.getBool("/mobs/" + std::to_string(i) + "/dropPowerup");

                std::string mobType = currentMapContent.getString("/mobs/" + std::to_string(i) + "/mobType");

                if (mobType == "cancerMob") {
                    EntityFactory::getInstance().spawnCancerMob(componentsContainer, eventHandler, position, dropPowerup);
                } else if (mobType == "pataPataMob") {
                    EntityFactory::getInstance().spawnPataPataMob(componentsContainer, eventHandler, position, dropPowerup);
                }

                currentMapContent.eraseKey("/mobs", i);
                mobsSize--;
            } else {
                i++;
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
                float speed = currentMapContent.getFloat("/parallax/" + std::to_string(i) + "/speed");
                Utils::Vect2 position(posX, posY);
                ParallaxType type = static_cast<ParallaxType>(currentMapContent.getInt("/parallax/" + std::to_string(i) + "/type"));
                EntityFactory::getInstance().spawnParallax(componentsContainer, eventHandler, position, -speed, layer, type, isLooping);
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
