/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpriteComponent
*/

#pragma once

#include "../../UtilsProject/Utils.hpp"
#include "AComponent.hpp"
#include <string>

namespace GameEngine {
class SpriteComponent : public AComponent {
  public:
    SpriteComponent(const std::string& imagePath, Vect2 pos, rect rect1, size_t layer) {
        this->imagePath = imagePath;
        this->pos = pos;
        this->rect1 = rect1;
        this->layer = layer;
    }
    ~SpriteComponent() = default;

    std::string getImagePath() const { return imagePath; }
    void setImagePath(const std::string& imagePath) { this->imagePath = imagePath; }
    Vect2 getPos() const { return pos; }
    void setPos(Vect2 pos) { this->pos = pos; }
    rect getRect() const { return rect1; }
    void setRect(rect rect1) { this->rect1 = rect1; }
    int getLayer() const { return layer; }
    void setLayer(int layer) { this->layer = layer; }
    Vect2 pos;
    rect rect1;

  private:
    size_t layer;
    std::string imagePath;
};
} // namespace GameEngine
