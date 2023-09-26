/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpriteComponent
*/

#pragma once

#include "../../GameEngine/Components/AComponent.hpp"
#include <string>

namespace GameEngine {
    class SpriteComponent : public AComponent {
    public:
        SpriteComponent(const std::string& imagePath, int x, int y, int width, int height) {
            this->imagePath = imagePath;
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }
        ~SpriteComponent() = default;

        std::string getImagePath() const { return imagePath; }
        void setImagePath(const std::string& imagePath) { this->imagePath = imagePath; }
        int getX() const { return x; }
        void setX(int x) { this->x = x; }
        int getY() const { return y; }
        void setY(int y) { this->y = y; }
        int getWidth() const { return width; }
        void setWidth(int width) { this->width = width; }
        int getHeight() const { return height; }
        void setHeight(int height) { this->height = height; }
        int getLayer() const { return layer; }
        void setLayer(int layer) { this->layer = layer; }

    private:
        size_t layer;
        std::string imagePath;
        int x, y, width, height;
    };
}
