cmake_minimum_required(VERSION 2.8)

project(OpenGLDemo)

include_directories(/home/dimrok/pers/sg)

# add our macro directory to cmake search path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

ADD_DEFINITIONS("-std=c++0x")

# check for OpenGL, GLEW and GLUT as our required dependencies
find_package (OpenGL)
if (NOT OPENGL_FOUND)
  message (FATAL_ERROR "OpengGL not found!")
endif ()


find_package (GLEW)
if (NOT GLEW_FOUND)
  message (FATAL_ERROR "GLEW not found!")
endif ()


find_package (GLU)
if (NOT GLU_FOUND)
  message (FATAL_ERROR "GLU not found!")
endif ()

find_package (GLFW)
if (NOT GLFW_FOUND)
  message (FATAL_ERROR "GLFW not found!")
endif ()

set(GL_LIBS
    ${GLFW_LIBRARY}
    ${GLEW_LIBRARY}
    ${OPENGL_LIBRARY}
    ${GLU_LIBRARY})

file(GLOB opengl_src
     *.cpp
     Comm/*.cpp
     SceneGraph/*.cpp
     SceneGraph/Interface/*.cpp
     SceneGraph/Scene/*.cpp
     SceneGraph/Node/*.cpp
     SceneGraph/Node/Test/*.cpp
     ShaderManager/*.cpp
     Test/*.cpp
)

add_executable(OpenGLDemo
     ${opengl_src}
)
target_link_libraries(OpenGLDemo
  ${GL_LIBS}
)
