cmake_minimum_required(VERSION 3.15)

find_package( OpenGL REQUIRED )

set(ProjName AEngine)

project(${ProjName})

# Define the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add definitions for UNICODE
add_definitions(-DUNICODE -D_UNICODE)

option(AENGINE_BUILD "Build as executable" ON) 

set(ProjSources 
    src/main.cpp
    src/Engine.cpp
    src/Level.cpp
    src/Object.cpp
    src/MacrosLibrary.cpp
    src/Render/Renderer.cpp
    src/Game.cpp
    src/Resources/ResourceManager.cpp
    src/Math/Mat4.cpp
    src/Render/Shape.cpp
)

set(ProjDefinitions)

if(OpenGL_FOUND)
    list(APPEND ProjDefinitions OPENGL)
    list(APPEND ProjSources 
        src/Render/OpenGL/GL_ShaderProgram.cpp
        src/Render/OpenGL/GL_Texture.cpp
        src/Render/OpenGL/GL_Sprite.cpp
    )
endif()

if (WIN32)
    list(APPEND ProjDefinitions WINDOWS)
    list(APPEND ProjSources 
        src/Render/Windows/WIN_Window.cpp
    )
endif()

# Add your source files and define the executable target
if(AENGINE_BUILD)
    add_executable(${ProjName} src/example.cpp ${ProjSources})
else()
    add_library(${ProjName} ${ProjSources})
endif()

target_compile_definitions(${ProjName} PRIVATE ${ProjDefinitions})

target_include_directories(${ProjName}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(external/glad)
target_link_libraries(${ProjName} glad)

add_custom_command(TARGET ${ProjName} POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy_directory
				   ${CMAKE_CURRENT_SOURCE_DIR}/resources 
                   ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/resources)
