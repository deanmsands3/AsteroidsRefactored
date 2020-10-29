cmake_minimum_required (VERSION 3.16)

project (AsteroidsRefactored)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add required packages
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(nlohmann_json 3.6.0 REQUIRED)

set(
        ASTEROID_SOURCES
        AsteroidsRefactored.cpp
        AsteroidsGame.cpp
        Game.cpp
        Player.cpp
        Bullet.cpp
        Asteroid.cpp
        Explosion.cpp
        Animation.cpp
        Entity.cpp
)

add_executable(${PROJECT_NAME} ${ASTEROID_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio nlohmann_json::nlohmann_json)
