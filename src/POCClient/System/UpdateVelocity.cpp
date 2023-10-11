//
// Created by Theophilus Homawoo on 11/10/2023.
//

#include "UpdateVelocity.hpp"

namespace Client {

    void UpdateVelocity::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {
        try {
            auto message = eventHandler.getTriggeredEvent().second;
            auto messageData = std::any_cast<std::shared_ptr<Network::Message>>(message);

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();

            if (ids.size() != 1 || args.size() != 2)
                return;
            auto velocityComponent = componentsContainer.getComponent(ids[0], GameEngine::ComponentsType::getComponentType("VelocityComponent"));
            if (!velocityComponent.has_value())
                return;
            float x = std::any_cast<float>(args[0]);
            float y = std::any_cast<float>(args[1]);

            auto velocity = std::any_cast<std::shared_ptr<GameEngine::VelocityComponent>>(velocityComponent);
            velocity->velocity = {x, y};

        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
    }

} // namespace Client