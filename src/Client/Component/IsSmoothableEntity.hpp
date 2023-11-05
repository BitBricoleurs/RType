//
// Created by clagasse on 10/31/23.
//

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "Vect2.hpp"

namespace Client {

    class IsSmoothableEntity : public GameEngine::AComponent {
    public:
        IsSmoothableEntity() = default;
        size_t getComponentType() override;
    };
}
