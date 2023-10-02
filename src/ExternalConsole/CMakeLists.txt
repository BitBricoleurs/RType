set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        NamedPipeIPC.cpp
        Commands/EchoCommand.cpp
        Commands/ExitCommand.cpp
        Terminal/Terminal.cpp
        main.cpp
        )



include_directories(
        ../UtilsProject
        Commands
        Terminal
        IPC
)

add_executable(DEVCONSOLE ${SOURCES})

target_include_directories(DEVCONSOLE PUBLIC
        /usr/local/include
        )
