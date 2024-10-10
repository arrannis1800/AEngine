cmake_minimum_required(VERSION 3.15)

find_package( OpenGL REQUIRED )

set(ProjName AEngine)

project(${ProjName})

# Define the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add definitions for UNICODE
add_definitions(-DUNICODE -D_UNICODE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add your source files and define the executable target
add_executable(${ProjName}
    src/test.cpp
    src/Engine.cpp
    src/Level.cpp
    src/Object.cpp
    src/MacrosLibrary.cpp
    src/Renderer.cpp
    src/Game.cpp
    src/Callbacks.cpp
)

add_subdirectory(external/glfw)
target_link_libraries(${ProjName} glfw)

add_subdirectory(external/glad)
target_link_libraries(${ProjName} glad)

