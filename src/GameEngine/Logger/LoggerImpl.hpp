//
// Created by Theophilus Homawoo on 30/10/2023.
//

#pragma once
#include <memory>

namespace GameEngine {
    std::unique_ptr<Logger::LoggerImpl> createLoggerImpl();
}

