#
#    Copyright 2017, infix development gmbh <admin@infix.ch>
#
#    This file is part of the Geometry Processing Pipeline (GPP) Library.
#
#    The GPP Library is free software: you can redistribute it and/or modify it
#    under the terms of the GNU Lesser General Public License as published
#    by the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    The GPP Library is distributed in the hope that it will
#    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
#    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with the GPP Library. If not, see <http://www.gnu.org/licenses/>.
#
#    @license LGPL-3.0+
#
#    Author: Aurel Gruber on 12.09.17.


cmake_minimum_required(VERSION 3.7)
project(GeometryProcessingPipeline)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external/OpenMesh)
include_directories(${OPENMESH_INCLUDE_DIRS})

find_path(GMP_INCLUDE_DIR gmp.h gmpxx.h
        PATHS ${GMP_PREFIX}/include /usr/include /usr/local/include )
find_library(GMP_LIBRARY NAMES gmp libgmp libgmpxx
        PATHS ${GMP_PREFIX}/lib /usr/lib /usr/local/lib)

include_directories(GMP_INCLUDE_DIR)

find_library(CORK_LIBRARY cork ${PROJECT_SOURCE_DIR}/external/cork/lib)

option(LIBIGL_WITH_OPENGL           "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW      "Use OpenGL GLFW"    ON)
option(LIBIGL_WITH_VIEWER      "Use OpenGL viewer"  ON)
set(LIBIGL_WITH_NANOGUI ON CACHE FORCE "Use Nanogui menu")
set(LIBIGL_WITH_EMBREE BOOL ON CACHE FORCE "Use Embree")

add_subdirectory("${PROJECT_SOURCE_DIR}/external/libigl/shared/cmake" "libigl")
include_directories(${LIBIGL_INCLUDE_DIRS})
add_definitions(${LIBIGL_DEFINITIONS})

add_subdirectory(external/GTest)

# for GPP clients
set(GPP_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${LIBIGL_INCLUDE_DIRS}
        ${OPENMESH_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/external/nanoflann/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/cork/include
        PARENT_SCOPE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/nanoflann/include)

# include cork for boolean operations
include_directories(
        external/cork/include
)

set(SOURCE_FILES

        GeometryViewer.cpp
        GeometryProcessor.cpp
        ProcessVisualizer.cpp
        Geometry.cpp
        AbstractStage.cpp
        GUIEntry.cpp
        GeometryHelpers.cpp
        PointCloudMatrixAdaptor.cpp
        BooleanOperation.cpp

        include/macros.h

        include/GeometryViewer.h
        include/GeometryProcessor.h
        include/ProcessVisualizer.h
        include/Geometry.h
        include/AbstractStage.h
        include/GUIEntry.h
        include/GeometryHelpers.h
        include/PointCloudMatrixAdaptor.h
        include/PointCloudHelpers.h
        include/BooleanOperation.h
        )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        ${LIBIGL_LIBRARIES}
        ${LIBIGL_VIEWER_EXTRA_LIBRARIES}
        ${LIBIGL_OPENGL_EXTRA_LIBRARIES}
        ${LIBIGL_OPENGL_GLFW_EXTRA_LIBRARIES}
        ${OPENMESH_LIBRARIES}
        ${CORK_LIBRARY}
        ${GMP_LIBRARY}
        ${LIBIGL_EMBREE_EXTRA_LIBRARIES}
        ${LIBIGL_EXTRA_LIBRARIES})

#testing
set(gtest_source
        tests/TestPointCloudMatrixAdaptor.cpp
        tests/run_GPP_tests.cpp
        ${SOURCE_FILES} tests/TestBooleanOperations.cpp)

add_executable(run_GPP_gtests ${gtest_source})

target_link_libraries(run_GPP_gtests
        gtest_main
        ${LIBIGL_LIBRARIES}
        ${LIBIGL_VIEWER_EXTRA_LIBRARIES}
        ${LIBIGL_OPENGL_EXTRA_LIBRARIES}
        ${LIBIGL_OPENGL_GLFW_EXTRA_LIBRARIES}
        ${OPENMESH_LIBRARIES}
        ${CORK_LIBRARY}
        ${GMP_LIBRARY})