//
// Created by Theophilus Homawoo on 11/10/2023.
//

#include "UpdatePosition.hpp"

namespace Client {

    void UpdatePosition::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {
        try {
            auto message = eventHandler.getTriggeredEvent().second;
            auto messageData = std::any_cast<std::shared_ptr<Network::Message>>(message);

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();

            if (ids.size() != 1 || args.size() != 2)
                return;
            auto positionComponent = componentsContainer.getComponent(ids[0], GameEngine::ComponentsType::getComponentType("PositionComponent"));
            if (!positionComponent.has_value())
                return;
            float x = std::any_cast<float>(args[0]);
            float y = std::any_cast<float>(args[1]);

            auto position = std::any_cast<std::shared_ptr<GameEngine::PositionComponent2D>>(positionComponent);
            position->pos = {x, y};

        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
    }

} // namespace Client