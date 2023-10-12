set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Utils)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Component)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System/Client)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Factory)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Utils)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME_POCCLIENT}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System/NetworkInput.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System/NetworkOutput.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Utils/Message.cpp

        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Component/NetworkClientId.cpp


        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/DeathAnimation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsBoss.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsPowerUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsStarship.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/MobComponents.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/SpriteAnimation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsBullet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Shooter.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/CreateBullet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/CreatePlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/EntityFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/LoadConfig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/MobSpawn.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkReceiveDisconnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkReceiveDisconnectApply.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkServerTimeout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkConnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkServerAccept.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/UpdatePosition.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/UpdateVelocity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/SyncPosSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ChangeDirPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/CreatePlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/CreateBullet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/CreateMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Shoot.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${PROJECT_NAME_POCCLIENT} PUBLIC GameEngine RenderEngineLib AudioEngineLib PhysicsEngineLib NetworkLib nlohmann_json::nlohmann_json)