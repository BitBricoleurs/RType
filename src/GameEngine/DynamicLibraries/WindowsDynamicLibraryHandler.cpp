//
// Created by Theophilus Homawoo on 04/11/2023.
//

// WindowsDynamicLibraryHandler.cpp
#ifdef _WIN32
#include "WindowsDynamicLibraryHandler.hpp"

bool WindowsDynamicLibraryHandler::loadLibrary(const std::string& libraryPath) {
    hModule = LoadLibraryA(libraryPath.c_str());
    return hModule != nullptr;
}

void WindowsDynamicLibraryHandler::closeLibrary() {
    if (hModule) {
        FreeLibrary(hModule);
        hModule = nullptr;
    }
}

std::function<void()> WindowsDynamicLibraryHandler::getFunction(const std::string& functionName) {
    FARPROC func = GetProcAddress(hModule, functionName.c_str());
    return reinterpret_cast<void(*)()>(func);
}
#endif
