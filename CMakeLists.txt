 # 
 # This file is part of the pneumatic game engine
 # 
 # Copyright (c) 2014 George Burton
 # 
 # THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
 # WARRANTY. IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES
 # ARISING FROM THE USE OF THIS SOFTWARE.
 # 
 # Permission is granted to anyone to use this software for any purpose,  
 # including commercial applications, and to alter it and redistribute it  
 # freely, subject to the following restrictions:
 # 
 #    1. The origin of this software must not be misrepresented; you must not  
 #       claim that you wrote the original software. If you use this software  
 #       in a product, an acknowledgment in the product documentation would be  
 #       appreciated but is not required.
 # 
 #    2. Altered source versions must be plainly marked as such, and must not be  
 #       misrepresented as being the original software.
 # 
 #    3. This notice may not be removed or altered from any source  
 #       distribution.
 # 
 # 

cmake_minimum_required (VERSION 2.8)

set(PROJECT_NAME pneumatic)
set(CMAKE_MAJOR_VERSION 0)
set(CMAKE_MINOR_VERSION 1)
project(${PROJECT_NAME})

# Source files
#==============
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(GRAPHICS_SRC_DIR "${SRC_DIR}/graphics")
set(GRAPHICS_SHAPES_SRC_DIR "${GRAPHICS_SRC_DIR}/shapes")

set(CORE_DIR "${SRC_DIR}/core")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

set(SOURCES
	"${CORE_DIR}/ResourceLoader.cpp"
	"${GRAPHICS_SRC_DIR}/Camera.cpp"
	"${GRAPHICS_SRC_DIR}/GlRenderer.cpp"
	"${GRAPHICS_SRC_DIR}/Light.cpp"
	"${GRAPHICS_SRC_DIR}/Mesh.cpp"
	"${GRAPHICS_SRC_DIR}/Shader.cpp"
	"${GRAPHICS_SRC_DIR}/ShaderUniform.cpp"
	"${GRAPHICS_SRC_DIR}/Sprite.cpp"
	"${GRAPHICS_SRC_DIR}/Texture.cpp"
	"${GRAPHICS_SRC_DIR}/RenderObject.cpp"
	"${GRAPHICS_SRC_DIR}/Window.cpp"
	"${GRAPHICS_SHAPES_SRC_DIR}/Ellipse.cpp")

include_directories(
	${SRC_DIR}
	${INCLUDE_DIR}
	${PROJECT_BINARY_DIR})

# System OpenGL and GLEW
#========================
find_package(OpenGL REQUIRED)

include_directories(
	${OPENGL_INCLUDE_DIRS}
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
set(GLFW_BUILD_DOCS "" OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL "" OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_DIR})
link_directories(${GLFW_DIR})
include_directories(${GLFW_INCLUDE_DIRS})

# GLM
#=====
set (GLM_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/thirdparty/glm")
add_subdirectory(${GLM_INCLUDE_DIRS})
link_directories(${GLM_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})

# GLEW
#======
set (GLEW_DIR "${PROJECT_SOURCE_DIR}/thirdparty/glew")
add_subdirectory (${GLEW_DIR})
link_directories (${GLEW_DIR})
include_directories (${GLEW_INCLUDE_DIR})

# Project build
#===============
add_library(${PROJECT_NAME} ${SOURCES})

add_definitions(
	-std=c++1y
	-Wall)

target_link_libraries(${PROJECT_NAME}
	${SOIL_LIBRARIES}
	${GLFW_LIBRARIES}
	${GLFW_LINK}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLU_LIBRARIES})
