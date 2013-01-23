cmake_minimum_required(VERSION 2.8)

project(OpenGLDemo)

include_directories ("${PROJECT_SOURCE_DIR}")

file(GLOB opengl_src
     *.cpp
     Comm/*.cpp
     SceneGraph/*.cpp
     ShaderManager/*.cpp
     Test/*.cpp
)

add_executable(OpenGLDemo
     ${opengl_src}
)
