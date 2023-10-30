//
// Created by Theophilus Homawoo on 13/10/2023.
//

#pragma once

#include "SpriteComponent.hpp"

namespace RenderEngine {
    class ButtonComponent : public SpriteComponent {
        public:
        ButtonComponent(const std::string& imagePath, Utils::Vect2 pos, Utils::rect rect1, size_t layer, float scale, float rotation, Utils::ColorR tint)
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

        std::string hoverEvent;
        std::string clickEvent;

        Utils::ColorR hoverColor;
        private:
            bool isHovered = false;

    };

} // GameEngine
