cmake_minimum_required(VERSION 2.8)
project(pneumatic_graphics)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(INCLUDE_PRIV "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(THIRDPARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")

set(PNEUMATIC_GRAPHICS_INCLUDE_DIRS "${INCLUDE_DIR}" PARENT_SCOPE)
set(PNEUMATIC_GRAPHICS_LIBRARIES "${PROJECT_NAME}" PARENT_SCOPE)

set(SOURCES
	# etc...
	"${SRC_DIR}/example.cpp")

add_subdirectory("${THIRDPARTY_DIR}")

include_directories(
	"${INCLUDE_DIR}"
	"${INCLUDE_PRIV}"
	"${GLM_INCLUDE_DIRS}"
	"${SOIL_INCLUDE_DIRS}"
	"${GLFW_INCLUDE_DIRS}")

target_link_libraries("${PROJECT_NAME}"
	"${OPENGL_LIBRARIES}"
	"${GLFW_LIBRARIES}"
	"${GLEW_LIBRARIES}"
	"${GLU_LIBRARIES}"
	"${SOIL_LIBRARIES}")

if (APPLE)
	include_directories("/System/Library/Frameworks")
	find_library(COCOA_LIBRARY Cocoa)
	find_library(QUARTZCORE_LIBRARY QuartzCore)
	find_library(IOKIT_LIBRARY IOKit)
	mark_as_advanced(COCOA_LIBRARY QUARTZCORE_LIBRARY IOKIT_LIBRARY)

	target_link_libraries("${PROJECT_NAME}"
		"${COCOA_LIBRARY}"
		"${QUARTZCORE_LIBRARY}"
		"${IOKIT_LIBRARY}")
endif()

add_library("${PROJECT_NAME}" OBJECT "${SOURCES}")
