//
// Created by Bartosz on 9/25/23.
//

#pragma once

#include "AComponent.hpp"
#include "../../UtilsProject/Utils.hpp"

namespace GameEngine {
    class ParallaxComponent : public AComponent {
    public:
        ParallaxComponent(const std::string& imagePath, Vector2 pos, rect rect1, int speed, int orientation, size_t layer) {
            this->imagePath = imagePath;
            this->speed = speed;
            this->pos = pos;
            this->rect1 = rect1;
            this->orientation = orientation;
            this->layer = layer;
        }
        ~ParallaxComponent() = default;

        std::string getImagePath() const { return imagePath; }
        void setImagePath(const std::string& imagePath) { this->imagePath = imagePath; }
        Vector2 getPos() const { return pos; }
        void setPos(Vector2 pos) { this->pos = pos; }
        rect getRect() const { return rect1; }
        void setRect(rect rect1) { this->rect1 = rect1; }
        int getOrientation() const { return orientation; }
        void setOrientation(int orientation) { this->orientation = orientation; }
        int getLayer() const { return layer; }
        void setLayer(int layer) { this->layer = layer; }
        int getSpeed() const { return speed; }
        void setSpeed(int speed) { this->speed = speed; }

    private:
        size_t layer;
        int orientation;
        std::string imagePath;
        rect rect1;
        Vector2 pos;
        int speed;
    };
}