set (CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.10)

project(tancodrom)
file(GLOB SOURCES Headers/*.h Sources/*.cpp)

add_executable(tancodrom ${SOURCES})
target_include_directories(tancodrom PRIVATE Headers)

# assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(tancodrom PRIVATE assimp::assimp)

# glew
find_package(GLEW REQUIRED)
target_link_libraries(tancodrom PRIVATE GLEW::GLEW)

# glfw3
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(tancodrom PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(tancodrom PRIVATE glm::glm)

find_package(Stb REQUIRED)
target_include_directories(tancodrom PRIVATE ${Stb_INCLUDE_DIR})