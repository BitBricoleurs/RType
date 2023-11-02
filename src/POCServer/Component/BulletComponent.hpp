//
// Created by clagasse on 11/1/23.
//

#include <cstddef>
#include <chrono>
#include "AComponent.hpp"
#include "BulletUtils.hpp"
#include "ComponentsType.hpp"

#pragma once

namespace Server {

    class BulletTypeComp : public GameEngine::AComponent {
    public:
      BulletTypeComp(BulletType type): type(type) {};

      size_t getComponentType() override;

        BulletType type;
    };

    class BulletOwnerComp : public GameEngine::AComponent {
    public:
      BulletOwnerComp(BulletOwner owner): owner(owner) {};

      size_t getComponentType() override;

        BulletOwner owner;
    };
}
