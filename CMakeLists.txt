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

set(ProjSources 
    src/test.cpp
    src/Engine.cpp
    src/Level.cpp
    src/Object.cpp
    src/MacrosLibrary.cpp
    src/Render/Renderer.cpp
    src/Game.cpp
)

if(OpenGL_FOUND)
    list(APPEND ProjSources 
        src/Render/OpenGL/GL_Window.cpp
        src/GL_Callbacks.cpp
    )
endif()

# Add your source files and define the executable target
add_executable(${ProjName}
    ${ProjSources}
)

target_compile_definitions(${ProjName} PRIVATE OPENGL)

target_include_directories(${ProjName}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(external/glfw)
target_link_libraries(${ProjName} glfw)

add_subdirectory(external/glad)
target_link_libraries(${ProjName} glad)

