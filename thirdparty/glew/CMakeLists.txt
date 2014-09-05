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
project(glew)
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add (
	glew
	PREFIX ${CMAKE_BINARY_DIR}/glew
	GIT_REPOSITORY https://github.com/nigels-com/glew
	TIMEOUT 10
	UPDATE_COMMAND ${GIT_EXECUTABLE} pull
	CONFIGURE_COMMAND make extensions
	BUILD_COMMAND make glew.lib
	BUILD_IN_SOURCE 1
	INSTALL_COMMAND ""
	LOG_DOWNLOAD ON)

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property (glew source_dir)
set (GLEW_INCLUDE_DIR "${source_dir}/include/GL" PARENT_SCOPE)
set (GLEW_LIBRARIES "${source_dir}/lib/libGLEW.a" PARENT_SCOPE)

