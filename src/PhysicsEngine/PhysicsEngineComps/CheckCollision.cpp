//
// Created by alexandre on 03/10/23.
//

#include "CheckCollision.hpp"

namespace PhysicsEngine {

    bool classCheckCollision::checkCollision(const Utils::Circle& a, const Utils::Circle& b)
    {
        float dx = a.center.x - b.center.x;
        float dy = a.center.y - b.center.y;
        float distanceSquared = dx * dx + dy * dy;
        float radiusSum = a.radius + b.radius;
        return distanceSquared <= radiusSum * radiusSum;
    }

    bool classCheckCollision::checkCollision(const Utils::rect& r, const Utils::Circle& c)
    {
        float rLeft = r.x;
        float rRight = r.x + r.w;
        float rTop = r.y;
        float rBottom = r.y + r.h;

        float closestX = std::clamp(c.center.x, rLeft, rRight);
        float closestY = std::clamp(c.center.y, rTop, rBottom);

        float dx = closestX - c.center.x;
        float dy = closestY - c.center.y;

        float distanceSquared = dx*dx + dy*dy;

        return distanceSquared < (c.radius * c.radius);
    }

    bool classCheckCollision::checkCollision(const Utils::rect& a, const Utils::rect& b)
    {
        float aLeft = a.x;
        float aRight = a.x + a.w;
        float aTop = a.y;
        float aBottom = a.y + a.h;

        float bLeft = b.x;
        float bRight = b.x + b.w;
        float bTop = b.y;
        float bBottom = b.y + b.h;

        return (aLeft < bRight && aRight > bLeft &&
                    aTop < bBottom && aBottom > bTop);
    }

}