//
// Created by Theophilus Homawoo on 04/11/2023.
//

#ifndef _WIN32
#include "DynamicLibraryHandler.hpp"
#include <dlfcn.h>

class UnixDynamicLibraryHandler : public DynamicLibraryHandler {
private:
    void* handle;

public:
    bool loadLibrary(const std::string& libraryPath) override;
    void closeLibrary() override;
    std::function<void()> getFunction(const std::string& functionName) override;
};
#endif

