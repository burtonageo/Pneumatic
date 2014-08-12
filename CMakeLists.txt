#
# CSC3223 Graphics for Games
# Coursework 2
# Name: George Burton
# Student Number: 110204567
# File: CMakeLists.txt
#

cmake_minimum_required (VERSION 2.8)

set(PROJECT_NAME pneumatic)
set(CMAKE_MAJOR_VERSION 0)
set(CMAKE_MINOR_VERSION 1)
project(${PROJECT_NAME})

# Source files
#==============
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(CORE_DIR "${SRC_DIR}/core")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

set(SOURCES
	"${SRC_DIR}/core/ResourceLoader.cpp"
	"${SRC_DIR}/graphics/Camera.cpp"
	"${SRC_DIR}/graphics/GlRenderer.cpp"
	"${SRC_DIR}/graphics/Window.cpp"
	"${SRC_DIR}/graphics/Light.cpp"
	"${SRC_DIR}/graphics/Mesh.cpp"
	"${SRC_DIR}/graphics/Shader.cpp"
	"${SRC_DIR}/graphics/Texture.cpp"
	"${SRC_DIR}/graphics/RenderObject.cpp")

include_directories(
	${SRC_DIR}
	${INCLUDE_DIR}
	${PROJECT_BINARY_DIR})

# System OpenGL and GLEW
#========================
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${GLU_INCLUDE_DIRS})

# SOIL
#======
set(SOIL_DIR "${PROJECT_SOURCE_DIR}/thirdparty/SOIL")
set(SOIL_INCLUDE_DIRS ${SOIL_DIR}/include)

add_subdirectory(${SOIL_DIR})
link_directories(${SOIL_DIR})
include_directories(${SOIL_INCLUDE_DIRS})

# GLFW
#======
set(GLFW_DIR "${PROJECT_SOURCE_DIR}/thirdparty/glfw")
set(GLFW_LINK "glfw")
set(GLFW_INCLUDE_DIRS "${GLFW_DIR}/include")

## disable GLFW tests, examples and docs
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL "Generate installation target" OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_DIR})
link_directories(${GLFW_DIR})
include_directories(${GLFW_INCLUDE_DIRS})

# GLM
#=====
set (GLM_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/thirdparty/glm")
include_directories(${GLM_INCLUDE_DIRS})

# Project build
#===============
add_library(${PROJECT_NAME} ${SOURCES})

add_definitions(
	-std=c++1y
	-Wall)

target_link_libraries(${PROJECT_NAME}
	${SOIL_LIBRARIES}
	${GLFW_LINK}
	${GLFW_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLU_LIBRARIES})