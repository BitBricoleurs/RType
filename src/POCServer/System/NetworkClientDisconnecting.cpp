//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkClientDisconnecting.hpp"

namespace Server {

void NetworkClientDisconnecting::update(
    GameEngine::ComponentsContainer &componentsContainer,
    GameEngine::EventHandler &eventHandler) {
  size_t entityId = 0;

  try {
    entityId = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
  } catch (std::bad_any_cast &e) {
    std::cerr << "Error from NetworkClientDisconnecting System " << e.what()
              << std::endl;
  }
  size_t componentType =
      GameEngine::ComponentsType::getComponentType("NetworkClientId");
  auto mayComp = componentsContainer.getComponent(entityId, componentType);
  if (!mayComp.has_value())
    return;
  auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());
  Network::Server::getInstance().disconnectClient(netIdComp->id);
  componentsContainer.deleteEntity(entityId);
  std::vector<size_t> ids = {entityId};
  std::vector<std::any> args = {};
  std::shared_ptr<Network::Message> message =
      std::make_shared<Network::Message>("DELETED_USER", ids, "", args);
  std::shared_ptr<Network::NotUserMessage> notMessage =
      std::make_shared<Network::NotUserMessage>(netIdComp->id, message);
  eventHandler.queueEvent("SEND_NETWORK", notMessage);
}

} // namespace Server