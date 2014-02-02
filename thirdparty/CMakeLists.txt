#
# CSC3223 Graphics for Games
# Coursework 2
# Name: George Burton
# Student Number: 110204567
# File: thirdparty/CMakeLists.txt
#

cmake_minimum_required(VERSION 2.8)

set(GLFW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glfw3")
set(GLFW ${GLFW_DIR} PARENT_SCOPE)
set(GLFW_LIBRARIES "glfw" PARENT_SCOPE)
set(GLFW_INCLUDE_DIRS "${GLFW_DIR}/include" PARENT_SCOPE)
add_subdirectory(${GLFW_DIR})

set(GLM_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/glm" PARENT_SCOPE)

set(SOIL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SOIL")
set(SOIL_LIBRARIES "SOIL" PARENT_SCOPE)
set(SOIL ${SOIL_DIR} PARENT_SCOPE)
set(SOIL_INCLUDE_DIRS "${SOIL_DIR}/include" PARENT_SCOPE)
add_subdirectory(${SOIL_DIR})