cmake_minimum_required (VERSION 2.6)

project (AsteroidsRefactored)

#Add required packages
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(AsteroidsRefactored AsteroidsRefactored.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio)
