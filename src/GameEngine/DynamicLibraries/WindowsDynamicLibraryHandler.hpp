//
// Created by Theophilus Homawoo on 04/11/2023.
//

#ifdef _WIN32
#include "DynamicLibraryHandler.hpp"
#include <windows.h>

class WindowsDynamicLibraryHandler : public DynamicLibraryHandler {
private:
    HMODULE hModule;

public:
    bool loadLibrary(const std::string& libraryPath) override;
    void closeLibrary() override;
    std::function<void()> getFunction(const std::string& functionName) override;
};
#endif

