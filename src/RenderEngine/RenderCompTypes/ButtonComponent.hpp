//
// Created by Theophilus Homawoo on 13/10/2023.
//

#pragma once

#include "SpriteComponent.hpp"

namespace GameEngine {
    class ButtonComponent : public SpriteComponent {
        public:
        ButtonComponent(const std::string& imagePath, Vect2 pos, rect rect1, size_t layer, float scale, float rotation, ColorR tint)
            : SpriteComponent(imagePath, pos, rect1, layer, scale, rotation, tint) {
            hoverColor.r = 255;
            hoverColor.b = 255;
            hoverColor.b = 0;
            hoverColor.a = 255;
        }

        ~ButtonComponent() override = default;

        enum ButtonState {
            NORMAL,
            HOVER,
            DISABLED
        };

        ButtonState state = NORMAL;

        size_t getComponentType() override;

        std::string hoverEvent = "";
        std::string clickEvent = "";

        ColorR hoverColor;
        private:
            bool isHovered = false;

    };

} // GameEngine
