/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpriteComponent
*/

#pragma once

#include "AComponent.hpp"
#include <string>
#include "../../UtilsProject/Utils.hpp"

namespace GameEngine {
    class SpriteComponent : public AComponent {
    public:
        SpriteComponent(const std::string& imagePath, Vector2 pos, rect rect1, size_t layer) {
            this->imagePath = imagePath;
            this->pos = pos;
            this->rect1 = rect1;
            this->layer = layer;
        }
        ~SpriteComponent() = default;

        std::string getImagePath() const { return imagePath; }
        void setImagePath(const std::string& imagePath) { this->imagePath = imagePath; }
        Vector2 getPos() const { return pos; }
        void setPos(Vector2 pos) { this->pos = pos; }
        rect getRect() const { return rect1; }
        void setRect(rect rect1) { this->rect1 = rect1; }
        int getLayer() const { return layer; }
        void setLayer(int layer) { this->layer = layer; }

    private:
        size_t layer;
        std::string imagePath;
        Vector2 pos;
        rect rect1;
    };
}
