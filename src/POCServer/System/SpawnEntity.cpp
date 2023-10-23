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
            std::cout << "Last map reached!" << std::endl;
        }
    }

    void SpawnEntity::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        currentTick++;

        int mobsSize = currentMapContent.getSize("/mobs");
        for (int i = 0; i < mobsSize;) {
            int tick = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/tick");

            if (currentTick == tick) {
                int posX = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/position/x");
                int posY = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/position/y");
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
                Utils::Vect2 position(posX, posY);

                ParallaxType type = static_cast<ParallaxType>(currentMapContent.getInt("/parallax/" + std::to_string(i) + "/type"));
                try {
                LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfigWithoutPath("config/Entity/createParallax.json");
                int parallaxSizeType = data.getSize("/types");
                for (int j = 0; j < parallaxSizeType; j++) {
                    if (static_cast<ParallaxType>(data.getInt("/types/" + std::to_string(j) + "/type")) == type) {
                        int layer = data.getInt("/types/" + std::to_string(j) + "/layer");
                        bool isLooping = data.getBool("/types/" + std::to_string(j) + "/isLooping");
                        EntityFactory::getInstance().spawnParallax(componentsContainer, eventHandler, position, layer, type, isLooping);
                    }
                }
                } catch (const std::exception& e) {
                     std::cerr << "Error loading map: " << e.what() << std::endl;
                     exit(1);
                }
                currentMapContent.eraseKey("/parallax", i);
                parallaxSize--;
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
}
