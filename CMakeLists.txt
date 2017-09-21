cmake_minimum_required(VERSION 3.7)
project(GeometryProcessingPipeline)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external/OpenMesh)
include_directories(${OPENMESH_INCLUDE_DIRS})


option(LIBIGL_WITH_OPENGL           "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW      "Use OpenGL GLFW"    ON)
option(LIBIGL_WITH_VIEWER      "Use OpenGL viewer"  ON)
set(LIBIGL_WITH_NANOGUI ON CACHE FORCE "Use Nanogui menu")

add_subdirectory("${PROJECT_SOURCE_DIR}/external/libigl/shared/cmake" "libigl")
include_directories(${LIBIGL_INCLUDE_DIRS})
add_definitions(${LIBIGL_DEFINITIONS})

set(GPP_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${LIBIGL_INCLUDE_DIRS}
        ${OPENMESH_INCLUDE_DIRS}
        PARENT_SCOPE)

set(SOURCE_FILES
        GeometryViewer.cpp
        GeometryProcessor.cpp
        ProcessVisualizer.cpp
        CLAParser.cpp
        Geometry.cpp
        AbstractStage.cpp
        GUIEntry.cpp
        GeometryHelpers.cpp

        include/macros.h

        include/GeometryViewer.h
        include/GeometryProcessor.h
        include/ProcessVisualizer.h
        include/CLAParser.h
        include/Geometry.h
        include/AbstractStage.h
        include/GUIEntry.h
        include/GeometryHelpers.h)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        ${LIBIGL_LIBRARIES}
        ${LIBIGL_VIEWER_EXTRA_LIBRARIES}
        ${LIBIGL_OPENGL_EXTRA_LIBRARIES}
        ${LIBIGL_OPENGL_GLFW_EXTRA_LIBRARIES}
        ${OPENMESH_LIBRARIES})
