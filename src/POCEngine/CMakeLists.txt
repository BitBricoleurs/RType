set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Factory)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Utils)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME_POCENGINE}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/BossStage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/BulletStartPosition.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Damage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/DeathAnimation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Health.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsBoss.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsBullet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsChargingBar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsParallax.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsPowerUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/SpriteAnimation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/NetworkClientId.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/EntityFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ChangeDirPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ChargingBar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/MobDeath.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Parallax.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ResetDirPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Shoot.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/SyncPosSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/UpdateEntitySprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/UpdateHealth.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkInput.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/NetworkOutput.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Server/NetworkClientConnection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Server/NetworkClientRequestDisconnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Server/NetworkClientDisconnecting.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Server/NetworkClientTimeout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Server/NetworkStartServer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkReceiveDisconnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkReceiveDisconnectApply.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkServerTimeout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkConnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils/Message.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${PROJECT_NAME_POCENGINE} PUBLIC GameEngine RenderEngineLib AudioEngineLib PhysicsEngineLib NetworkLib)