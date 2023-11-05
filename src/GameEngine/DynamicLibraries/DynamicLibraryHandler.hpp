//
// Created by Theophilus Homawoo on 04/11/2023.
//

#pragma once

#include <string>
#include <functional>

class DynamicLibraryHandler {
public:
    virtual ~DynamicLibraryHandler() = default;

    virtual bool loadLibrary(const std::string& libraryPath) = 0;
    virtual void closeLibrary() = 0;
    virtual std::function<void()> getFunction(const std::string& functionName) = 0;
};

