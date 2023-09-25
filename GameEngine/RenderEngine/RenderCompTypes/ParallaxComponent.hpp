//
// Created by Bartosz on 9/25/23.
//

#pragma once

#include "../Components/AComponent.hpp"

namespace GameEngine {
    class ParallaxComponent : public AComponent {
    public:
        ParallaxComponent(const std::string& imagePath, int x, int y, int width, int height, int speed) {
            this->imagePath = imagePath;
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
            this->speed = speed;
        }
        ~ParallaxComponent();

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
        int getSpeed() const { return speed; }
        void setSpeed(int speed) { this->speed = speed; }
        int getOrientation() const { return orientation; }
        void setOrientation(int orientation) { this->orientation = orientation; }
    private:
        size_t layer;
        int orientation;
        std::string imagePath;
        int x, y, width, height, speed;
    };
}