//
// Created by Bartosz on 10/24/23.
//

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include "RenderEngineCinematicSystem.hpp"
#include "RenderEngineSystem.hpp"
#include "GameEngine.hpp"

namespace py = pybind11;

int main() {
    // Start the Python interpreter
    py::scoped_interpreter guard{};

    GameEngine::GameEngine engine;
    auto render = std::make_shared<RenderEngine::RenderEngineSystem>("Window", engine);
    auto cinematic = std::make_shared<RenderEngine::RenderEngineCinematicSystem>();
    engine.addSystem("Render", render);
    engine.addEvent("Cinematic", cinematic);

    // Expose the game engine to Python
    py::module_ m = py::module_::import("__main__");
    py::object globals = m.attr("__dict__");
    globals["engine"] = py::cast(&engine);

    // Load and execute the Python script
    try {
        py::exec(R"(
            # Python script content
            print("Running Python script...")
            cinematic = engine.getEvent("Cinematic")
            cinematic.playCinematic("intro_cinematic")
        )", globals);
    } catch (py::error_already_set &e) {
        std::cerr << "Python Error: " << e.what() << std::endl;
    }

    engine.run();

    return 0;
}