set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME_HUNTER} PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)
target_include_directories(${PROJECT_NAME_HUNTER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Components)
target_include_directories(${PROJECT_NAME_HUNTER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Systems)
target_include_directories(${PROJECT_NAME_HUNTER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME_HUNTER}
        PRIVATE
        
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/SpawnBird.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/SyncPosSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/Animate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/KillBird.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/AnimateDeath.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/AnimateShot.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/Shoot.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/UpdateScore.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/DetectLifeLost.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/GameOver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/StartNewGame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/CurveDown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/IncreaseDifficulty.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${PROJECT_NAME_HUNTER} PUBLIC GameEngine RenderEngineLib AudioEngineLib PhysicsEngineLib)
