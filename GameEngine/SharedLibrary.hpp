//
// Created by Theophilus Homawoo on 20/09/2023.
//

#pragma once

#include <string>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif


namespace GameEngine {
    class SharedLibrary {
        public:
            SharedLibrary(const std::string& path) {
                #ifdef _WIN32
                    handle = LoadLibrary(path.c_str());
                #else
                    handle = dlopen(path.c_str(), RTLD_NOW);
                #endif
                if (!handle) {
                    // NE PAS OUBLIER CUSTOM ERRORS
                }
            }
            ~SharedLibrary() {
                #ifdef _WIN32
                    FreeLibrary(handle);
                #else
                    dlclose(handle);
                #endif
            }

            void* getFunction(const std::string& functionName) {
                #ifdef _WIN32
                    return GetProcAddress(handle, functionName.c_str());
                #else
                    return dlsym(handle, functionName.c_str());
                #endif
            }

        private:
        #ifdef _WIN32
            HMODULE handle;
        #else
            void* handle;
        #endif
    };
} // namespace GameEngine
