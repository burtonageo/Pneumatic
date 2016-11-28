/**
 * This file is part of the pneumatic game engine
 *
 * Copyright (c) 2014 George Burton
 *
 * THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY. IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES
 * ARISING FROM THE USE OF THIS SOFTWARE.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *       claim that you wrote the original software. If you use this software
 *       in a product, an acknowledgment in the product documentation would be
 *       appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *       misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *       distribution.
 *
 **/

#include "pneu/graphics/ShaderUniform.hpp"
#include "pneu/graphics/Shader.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"

#include <glm/glm.hpp>

#pragma clang diagnostic pop


#define DECLARE_SHADERUNIFORM(type, update_function) \
    template<> \
    auto \
    pneu::graphics::ShaderUniform<type>::update(const type& uniform_value) -> void    \
    { \
        ShaderId variable_id = fShader->getShaderProgram(); \
        auto variable_ref = glGetUniformLocation(variable_id, fVariableName.c_str()); \
        update_function; \
    }

DECLARE_SHADERUNIFORM(float,                glUniform1f(variable_ref, uniform_value))
DECLARE_SHADERUNIFORM(int,                    glUniform1i(variable_ref, uniform_value))
DECLARE_SHADERUNIFORM(unsigned int, glUniform1i(variable_ref, uniform_value))

DECLARE_SHADERUNIFORM(glm::vec2, glUniform2f(variable_ref, uniform_value.x, uniform_value.y))
DECLARE_SHADERUNIFORM(glm::vec3, glUniform3f(variable_ref, uniform_value.x, uniform_value.y, uniform_value.z))
DECLARE_SHADERUNIFORM(glm::vec4, glUniform4f(variable_ref, uniform_value.x, uniform_value.y, uniform_value.z,
                                                           uniform_value.w))

DECLARE_SHADERUNIFORM(glm::ivec2, glUniform2i(variable_ref, uniform_value.x, uniform_value.y))
DECLARE_SHADERUNIFORM(glm::ivec3, glUniform3i(variable_ref, uniform_value.x, uniform_value.y, uniform_value.z))
DECLARE_SHADERUNIFORM(glm::ivec4, glUniform4i(variable_ref, uniform_value.x, uniform_value.y, uniform_value.z,
                                                            uniform_value.w))

DECLARE_SHADERUNIFORM(glm::uvec2, glUniform2ui(variable_ref, uniform_value.x, uniform_value.y))
DECLARE_SHADERUNIFORM(glm::uvec3, glUniform3ui(variable_ref, uniform_value.x, uniform_value.y, uniform_value.z))
DECLARE_SHADERUNIFORM(glm::uvec4, glUniform4ui(variable_ref, uniform_value.x, uniform_value.y, uniform_value.z,
                                                             uniform_value.w))

DECLARE_SHADERUNIFORM(glm::mat4,  glUniformMatrix4fv(variable_ref, 1, GL_FALSE, &uniform_value[0][0]))
