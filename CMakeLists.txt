cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 23)

project(tancodrom)
file(GLOB SRC_FILES Headers/*.h Sources/*.cpp)

add_executable(tancodrom ${SRC_FILES})
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

find_package(SFML COMPONENTS system audio CONFIG REQUIRED)
target_link_libraries(tancodrom PRIVATE sfml-system sfml-audio)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Vertex Shaders" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Fragment Shaders" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Models" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})