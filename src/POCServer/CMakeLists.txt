set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Utils)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Component)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Factory)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME_POCSERVER}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Utils/Message.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System/NetworkInput.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System/NetworkOutput.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Component/NetworkClientId.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/Component/BossStage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Damage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Health.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/HeightVariation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsBoss.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsPowerUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/MobComponents.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Shooter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsBullet.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/CreateBullet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/CreatePlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/EntityFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/LoadConfig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/MobSpawn.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkClientConnection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkClientDisconnecting.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkClientRequestDisconnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkClientTimeout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkStartServer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkUpdateWorld.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkMoveClient.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkShootClient.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME_POCSERVER} PUBLIC GameEngine PhysicsEngineLib NetworkLib nlohmann_json::nlohmann_json)