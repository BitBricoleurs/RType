cmake_minimum_required(VERSION 3.15)

include(FetchContent)

set(LUABRIDGE_REPO_URL "https://github.com/vinniefalco/LuaBridge.git")
set(LUABRIDGE_VERSION "3.0")

FetchContent_Declare(
        LuaBridge
        GIT_REPOSITORY ${LUABRIDGE_REPO_URL}
)
FetchContent_MakeAvailable(LuaBridge)