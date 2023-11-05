//
// Created by Theophilus Homawoo on 04/11/2023.
//

#ifndef _WIN32
#include "UnixDynamicLibraryHandler.hpp"

bool UnixDynamicLibraryHandler::loadLibrary(const std::string& libraryPath) {
    handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    return handle != nullptr;
}

void UnixDynamicLibraryHandler::closeLibrary() {
    if (handle) {
        dlclose(handle);
        handle = nullptr;
    }
}

std::function<void()> UnixDynamicLibraryHandler::getFunction(const std::string& functionName) {
    void* func = dlsym(handle, functionName.c_str());
    return reinterpret_cast<void(*)()>(func);
}
#endif
