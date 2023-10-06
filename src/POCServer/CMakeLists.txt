set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Utils)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME_POCSERVER}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/NetworkClientId.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils/Message.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkClientConnection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkClientDisconnecting.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkClientRequestDisconnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkClientTimeout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkInput.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkOutput.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkStartServer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME_POCSERVER} PUBLIC GameEngine PhysicsEngineLib NetworkLib)