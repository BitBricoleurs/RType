/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Vec2f
*/

#ifndef VEC2F_HPP_
#define VEC2F_HPP_

namespace GameEngine {
    class Vec2f {
    public:
        Vec2f(float x, float y) : x(x), y(y) {}
        float x, y;
    };
} // namespace GameEngine

#endif /* !VEC2F_HPP_ */
