//
// Created by Bartosz on 10/31/23.
//

#include "ISystem.hpp"
#include "ComponentContainer.hpp"
#include "PhysicsEngine.hpp"

namespace PhysicsEngine {

    class PhysicsEngineUpdateHitboxes: public GameEngine::ISystem {
    public:
        PhysicsEngineUpdateHitboxes();
        ~PhysicsEngineUpdateHitboxes()  = default;

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) override;
    private:
        std::unique_ptr<PhysicsEngine> engine;
    };
}
