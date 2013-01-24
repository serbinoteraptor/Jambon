# - Try to find GLFW
# Once done this will define
#
#  GLFW_FOUND        - system has GLFW
#  GLFW_INCLUDE_DIR  - the GLFW include directory
#  GLFW_LIBRARY_DIR  - where the libraries are
#  GLFW_LIBRARY      - Link these to use GLFW
#

IF (GLFW_INCLUDE_DIR)
  # Already in cache, be silent
  SET(GLFW_FIND_QUIETLY TRUE)
ENDIF (GLFW_INCLUDE_DIR)

FIND_PATH( GLFW_INCLUDE_DIR GL/glfw.h GL/wglfw.h
           PATHS /usr/local/include /usr/include )
SET( GLFW_NAMES glfw GLFW )
FIND_LIBRARY( GLFW_LIBRARY
              NAMES ${GLFW_NAMES}
              PATHS /usr/lib /usr/local/lib )

GET_FILENAME_COMPONENT( GLFW_LIBRARY_DIR ${GLFW_LIBRARY} PATH )

IF (GLFW_INCLUDE_DIR AND GLFW_LIBRARY)
   SET(GLFW_FOUND TRUE)
ELSE (GLFW_INCLUDE_DIR AND GLFW_LIBRARY)
   SET( GLFW_FOUND FALSE )
   SET( GLFW_LIBRARY_DIR )
ENDIF (GLFW_INCLUDE_DIR AND GLFW_LIBRARY)
