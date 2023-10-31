//
// Created by Bartosz on 10/31/23.
//

#include <pybind11/pybind11.h>
#include "RenderEngineCinematicSystem.hpp"
#include "ComponentContainer.hpp"
#include "EventHandler.hpp"

namespace py = pybind11;

PYBIND11_MODULE(cinematic_module, m) {
    try {
        py::class_<GameEngine::ComponentsContainer, std::shared_ptr<GameEngine::ComponentsContainer>>(m, "ComponentsContainer")
        .def(py::init<>())
        .def("createEntity", (size_t (GameEngine::ComponentsContainer::*)()) &GameEngine::ComponentsContainer::createEntity)
        .def("createEntity", (size_t (GameEngine::ComponentsContainer::*)(std::vector<std::optional<std::shared_ptr<GameEngine::IComponent>>>)) &GameEngine::ComponentsContainer::createEntity)
            .def("bindComponentToEntity", &GameEngine::ComponentsContainer::bindComponentToEntity)
            ;
            
        py::class_<GameEngine::EventHandler, std::shared_ptr<GameEngine::EventHandler>>(m, "EventHandler")
            .def(py::init<>())
            .def("triggerEvent", &GameEngine::EventHandler::triggerEvent)
            ;

        py::class_<RenderEngine::RenderEngineCinematicSystem, std::shared_ptr<RenderEngine::RenderEngineCinematicSystem>>(m, "RenderEngineCinematicSystem")
            .def(py::init<>())
            .def("update", &RenderEngine::RenderEngineCinematicSystem::update)
            .def("playCinematic", &RenderEngine::RenderEngineCinematicSystem::playCinematic)
            .def("endCinematic", &RenderEngine::RenderEngineCinematicSystem::endCinematic)
            .def("loadJSON", &RenderEngine::RenderEngineCinematicSystem::loadJSON);
    } catch (pybind11::error_already_set &e) {
        std::cout << "Python error: " << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cout << "C++ exception: " << e.what() << std::endl;
    }
}