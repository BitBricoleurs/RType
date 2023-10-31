//
// Created by Theophilus Homawoo on 24/09/2023.
//

#include "GameEngine.hpp"

#include <utility>

namespace GameEngine {
    std::map<std::string, GameEngine::CommandFunction> GameEngine::commands;

    GameEngine::GameEngine() : tickSpeed(1.0 / 60.0), isRunning(true) {
        eventHandler.addEvent("gameEngineStop", [this] { this->stop(); });
        eventHandler.addEvent("gameEngineChangeScene", [this](const std::any& sceneName) { this->changeScene(sceneName); });
        eventHandler.addEvent("ENTER_KEY_PRESSED", [this] { this->launch_cpp_program("Console", "localhost 9191"); });

        registerCommand("print", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() > 0) {
                return args[0] + "\n";
            } else {
                return "No argument provided for print command.\n";
            }
        });

        registerCommand("add", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() >= 2) {
                int a = std::stoi(args[0]);
                int b = std::stoi(args[1]);
                return "Result: " + std::to_string(a + b) + "\n";
            } else {
                return "Not enough arguments provided for add command.\n";
            }
        });

        registerCommand("subtract", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() >= 2) {
                int a = std::stoi(args[0]);
                int b = std::stoi(args[1]);
                return "Result: " + std::to_string(a - b) + "\n";
            } else {
                return "Not enough arguments provided for subtract command.\n";
            }
        });

        registerCommand("changeTickSpeed", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() >= 1) {
                double newTickSpeed = std::stod(args[0]);
                this->setTickSpeed(newTickSpeed);
                return "Tick speed changed to " + std::to_string(newTickSpeed) + "\n";
            } else {
                return "Not enough arguments provided for changeTickSpeed command.\n";
            }
        });

        registerCommand("changeScene", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() >= 1) {
                queueEvent("gameEngineChangeScene", args[0]);
                return "Scene changed to " + args[0] + "\n";
            } else {
                return "Not enough arguments provided for changeScene command.\n";
            }
        });

        registerCommand("listScenes", [this](const std::vector<std::string>& args) -> std::string {
            std::string sceneList = "Scenes: ";
            if (sceneMap.empty()) {
                return "No scenes found.\n";
            }
            for (const auto& scene : sceneMap) {
                sceneList += scene.first + ", ";
            }
            return sceneList + "\n";
        });

        registerCommand("scheduleEvent", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() >= 3) {
                std::string eventName = args[0];
                size_t interval = std::stoi(args[1]);
                std::string eventData = args[2];
                if (args.size() >= 4) {
                    size_t repeat = std::stoi(args[3]);
                    this->scheduleEvent(eventName, interval, eventData, repeat);
                    return "Event scheduled: " + eventName + " with repeat " + std::to_string(repeat) + "\n";
                }
                this->scheduleEvent(eventName, interval, eventData);
                return "Event scheduled: " + eventName + "\n";
            } else {
                return "Not enough arguments provided for scheduleEvent command.\n";
            }
        });

        registerCommand("unscheduleEvent", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() >= 1) {
                std::string eventName = args[0];
                if (args.size() >= 2) {
                    std::string eventData = args[1];
                    this->unscheduleEvent(eventName, eventData);
                    return "Event unscheduled: " + eventName + " with eventData " + eventData + "\n";
                }
                this->unscheduleEvent(eventName);
                return "Event unscheduled: " + eventName + "\n";
            } else {
                return "Not enough arguments provided for unscheduleEvent command.\n";
            }
        });

        registerCommand("listCommands", [this](const std::vector<std::string>& args) -> std::string {
            std::string commandList = "Commands: ";
            for (const auto& command : commands) {
                commandList += command.first + ", ";
            }
            return commandList + "\n";
        });

        registerCommand("log", [this](const std::vector<std::string>& args) -> std::string {
            bool actualState = Logger::wantsToReceiveLogs;
            Logger::wantsToReceiveLogs = !actualState;
            return "Logger state changed to " + std::to_string(!actualState) + "\n";
        });

        registerCommand("pause", [this](const std::vector<std::string>& args) -> std::string {
            bool actualState = pause;
            pause = !actualState;
            return "Pause state changed to " + std::to_string(!actualState) + "\n";
        });
    }

    GameEngine::~GameEngine() = default;

    size_t GameEngine::createEntity() {
        return registry.createEntity();
    }

    size_t GameEngine::createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components) {
        return registry.createEntity(std::move(components));
    }

    void GameEngine::bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component) {
        registry.bindComponentToEntity(entityID, std::move(component));
    }

    void GameEngine::unbindComponentFromEntity(size_t entityID, size_t componentType) {
        registry.unbindComponentFromEntity(entityID, componentType);
    }

    void GameEngine::addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority) {
        registry.addSystem(systemName, std::move(system), priority);
    }

    void GameEngine::bindSceneInitiation(const std::string& sceneName, std::function<void(GameEngine&)> sceneInitiation) {
        sceneMap[sceneName] = std::move(sceneInitiation);
    }

    void GameEngine::changeScene(const std::any& sceneName) {
        try {
            auto sceneNameString = std::any_cast<std::string>(sceneName);
            if (sceneMap.find(sceneNameString) == sceneMap.end()) {
                std::cerr << "Error: Scene name not found!" << std::endl;
                return;
            }
            eventHandler.clear();
            registry.clear();
            sceneMap[sceneNameString](*this);
            eventHandler.addEvent("gameEngineStop", [this] { this->stop(); });
            eventHandler.addEvent("gameEngineChangeScene", [this](const std::any& sceneName) { this->changeScene(sceneName); });

        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error: Scene name must be a string!" << std::endl;
            return;
        }
    }

    void GameEngine::setTickSpeed(double newTickSpeed) {
        tickSpeed = newTickSpeed;
    }

    void GameEngine::scheduleEvent(const std::string& eventName, size_t interval, const std::any& eventData, size_t repeat) {
        eventHandler.scheduleEvent(eventName, interval, eventData, repeat);
    }

    void GameEngine::unscheduleEvent(const std::string& eventName, const std::any& eventData) {
        eventHandler.unscheduleEvent(eventName, eventData);
    }

    void GameEngine::run() {
        Timer timer;
        double lastTickTime = 0.0;

        std::thread server_thread([]{ Logger::startServer(9191); });
        server_thread.detach();
        while (isRunning) {
            double currentTime = timer.elapsedSeconds();
            if ((currentTime - lastTickTime >= tickSpeed) && !pause) {
                update();
                lastTickTime = currentTime;
            } else {
                int sleepTime = static_cast<int>((tickSpeed - (currentTime - lastTickTime)) * 1000);
                if (sleepTime > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
                }
            }
        }
    }

    void GameEngine::addEvent(const std::string& eventName, std::shared_ptr<ISystem> system) {
        eventHandler.addEvent(eventName, std::move(system));
    }

    void GameEngine::addEvent(const std::string& eventName, std::function<void()> function) {
        eventHandler.addEvent(eventName, std::move(function));
    }

    void GameEngine::addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems) {
        eventHandler.addEvent(eventName, systems);
    }

    void GameEngine::deleteEvent(const std::string& eventName) {
        eventHandler.deleteEvent(eventName);
    }

    void GameEngine::update() {
        registry.updateSystems(eventHandler);
        eventHandler.updateScheduledEvents();
    }

    void GameEngine::stop() {
        isRunning = false;
    }

    void GameEngine::setContinuousEvent(const std::string& eventName, const std::string& continuousEventName) {
        eventHandler.setContinuousEvent(eventName, continuousEventName);
    }

    void GameEngine::removeContinuousEvent(const std::string& eventName) {
        eventHandler.removeContinuousEvent(eventName);
    }

    void GameEngine::queueEvent(const std::string& eventName, const std::any& eventData) {
        eventHandler.queueEvent(eventName, eventData);
    }

    std::string GameEngine::handleDevConsole(std::string inputCommand) {
        std::istringstream iss(inputCommand);
        std::string command;
        std::vector<std::string> args;

        iss >> command;

        std::string arg;
        while (iss >> arg) {
            args.push_back(arg);
        }
        auto it = commands.find(command);
        if (it != commands.end()) {
            return it->second(args);
        } else {
            return "Command not found: " + command;
        }
    }

    void GameEngine::registerCommand(const std::string& command, CommandFunction function) {
        commands[command] = std::move(function);
    }
}
