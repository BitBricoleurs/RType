//
// Created by Bartosz on 10/31/23.
//

#pragma once

#include <string>
extern "C" {
    #include "luajit-2.1/luajit.h"
    #include "luajit-2.1/lualib.h"
    #include "luajit-2.1/lauxlib.h"
}
#include <stdexcept>
#include "LuaBridge/LuaBridge.h"

namespace LuaScriptingEngine {
    class LuaScriptingEngine {
    public:
        LuaScriptingEngine() {
            L = luaL_newstate();
            if (!L) throw std::runtime_error("Failed to create Lua state");
            luaL_openlibs(L);
        }

        ~LuaScriptingEngine() {
            if (L) {
                lua_close(L);
                L = nullptr;
            }
        }

        void runScript(const std::string& script) {
            if (luaL_dostring(L, script.c_str()) != LUA_OK) {
                const char* errorMessage = lua_tostring(L, -1);
                throw std::runtime_error("Lua error: " + std::string(errorMessage));
            }
        }

        void exposeFunction(const char* name, lua_CFunction function) {
            lua_pushcfunction(L, function);
            lua_setglobal(L, name);
        }

        [[nodiscard]] lua_State* getState() const {
            return L;
        }

    private:
        lua_State* L;
    };
}
