cmake_minimum_required (VERSION 2.6)

project (AsteroidsRefactored)

#Add required packages
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(
	ASTEROID_SOURCES
	AsteroidsRefactored.cpp
	Player.cpp
	Bullet.cpp
	Asteroid.cpp
	Explosion.cpp
	Animation.cpp
	Entity.cpp
)

add_executable(AsteroidsRefactored ${ASTEROID_SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio)
