set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Utils)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Component)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System/Client)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Factory)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Utils)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME_POCENGINE}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/BossStage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Damage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/DeathAnimation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Health.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsBoss.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsBullet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsChargingBar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsForcePod.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsParallax.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/IsPowerUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Shooter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/SpriteAnimation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/isHealthBar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Score.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/MobComponents.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/HeightVariation.cpp
        ../RenderEngine/RenderCompTypes/WindowInfoComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/EntityFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/MobSpawn.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/CreatePlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Factory/CreateBullet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/AnimateOnMove.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ChangeDirPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ChargingBar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ForcePodSpawn.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/InitParallax.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/MobDeath.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Parallax.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ResetDirPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/RollBackBorder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/ParallaxPlanet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Shoot.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/DeleteEntities.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/SyncPosSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/TestInput.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/UpdateEntitySprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/UpdateHealth.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System/NetworkInput.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/System/NetworkOutput.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Utils/Message.cpp
        ${CMAKE_SOURCE_DIR}/src/SharedNetwork/Component/NetworkClientId.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkReceiveDisconnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkReceiveDisconnectApply.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkServerTimeout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkConnect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/Client/NetworkServerAccept.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/SpawnMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/WiggleMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/CreatePlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/RemoveHealth.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/UpdateScore.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/SpawnMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/WiggleMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/CreatePlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/CollisionHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/PlayerHit.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/PlayerHitMob.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/MobHit.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/SpawnPowerUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/isPowerUpPickUp.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${PROJECT_NAME_POCENGINE} PUBLIC GameEngine RenderEngineLib AudioEngineLib PhysicsEngineLib NetworkLib)