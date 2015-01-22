cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(IMAGE_VIEWER)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)


#########################################################
# FIND FLTK
#########################################################

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})
link_directories(${FLTK_LIBRARY_DIRS})
add_definitions(${FLTK_DEFINITIONS})
#########################################################
# FIND OPENCV
#########################################################

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_CFLAGS_OTHER})


#########################################################
# Include Files
#########################################################
add_executable(demo demo.cpp imageviewer.hpp JMD_Vision_Image.cpp)

########################################################
# Linking & stuff
#########################################################

  # create the program “demo”
  target_link_libraries(demo ${FLTK_LIBRARIES} ${OpenCV_LIBRARIES} -ldl)

