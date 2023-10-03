/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpriteComponent
*/

#pragma once

#include "AComponent.hpp"
#include <string>
#include "Utils.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class SpriteComponent : public AComponent {
    public:
        SpriteComponent(const std::string& imagePath, Vect2 pos, rect rect1, size_t layer, float scale, float rotation, ColorR tint) {
            this->imagePath = imagePath;
            this->pos = pos;
            this->rect1 = rect1;
            this->layer = layer;
            this->rotation = rotation;
            this->scale = scale;
            this->tint = tint;
        }
        ~SpriteComponent() = default;

        std::string getImagePath() const { return imagePath; }
        void setImagePath(const std::string& imagePath) { this->imagePath = imagePath; }
        Vect2 getPos() const { return pos; }
        void setPos(Vect2 pos) { this->pos = pos; }
        rect getRect() const { return rect1; }
        void setRect(rect rect1) { this->rect1 = rect1; }
        size_t getLayer() const { return layer; }
        void setLayer(int layer) { this->layer = layer; }
        size_t getComponentType() override { return ComponentsType::getNewComponentType("SpriteComponent"); }
        float getScale() const { return scale; }
        void setScale(float scale) { this->scale = scale; }
        int getWidth() const { return rect1.w; }
        float getRotation() const { return rotation; }
        void setRotation(float rotation) { this->rotation = rotation;}
        Vect2 getOrigin() const { return origin;}
        void setOrigin(Vect2 origin) { this->origin = origin;}
        ColorR getTint() const {return tint;}
        void setTinit(ColorR tint) { this->tint = tint;}

    private:
        float scale;
        float rotation;
        size_t layer;
        std::string imagePath;
        Vect2 pos;
        rect rect1;
        Vect2 origin;
        ColorR tint;
    };
}
