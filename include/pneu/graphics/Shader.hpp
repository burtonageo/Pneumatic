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

#pragma once

#ifndef PNEUMATIC_SHADER_HPP
#define PNEUMATIC_SHADER_HPP

#include <string>
#include <utility>
#include <vector>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#endif

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#include "pneu/core/FuncResult.hpp"

using ShaderId = GLuint;

namespace pneu {

namespace graphics {

/**
 * A class to encapsulate a graphical shader written in
 * GLSL for OpenGL. Does not support compute shaders.
 */
class Shader final {
public:
    /**
     * Creates an unitialised shader.
     *
     * @note Initialise it using either the loadFromFile or the
     *       initWithCode methods to create a shader on the GPU
     *       from a source string or file.
     */
    Shader();

    /**
     * Destroys the shader, and frees the GPU shader resource.
     */
    ~Shader();

    /**
     * Initialises the shader with the contents of the source files.
     *
     * @param vert_file The vertex shader file
     * @param frag_file The fragment shader file
     * @param geom_file The geometry shader file. This parameter is optional.
     * @param tcs_file  The tessalation control shader file. This parameter is optional.
     * @param tes_file  The tesselation evaluation shader file. This parameter is optional.
     *
     * @return Whether the shader was successfully initialised from the shader files.
     *         Fails if any files could not be loaded or the vertex shader or fragment
     *         shader files are not present, or there was a syntax error in the shaders.
     */
    auto loadFromFile(const std::string& vert_file,
                                        const std::string& frag_file,
                                        const std::string& geom_file = "",
                                        const std::string& tcs_file    = "",
                                        const std::string& tes_file    = "") -> pneu::core::MethodResult;

    /**
     * Initialises the shader with inline code from a string variable.
     *
     * @param vert_source The vertex shader source.
     * @param frag_source The fragment shader source.
     * @param geom_source The geometry shader source. This parameter is optional.
     * @param tcs_source    The tessalation control shader source. This parameter is optional.
     * @param tes_source    The tesselation evaluation shader source. This parameter is optional.
     *
     * @return Whether the shader was successfully initialised from the shader sources.
     *                 Fails if either vert_source or frag_source are blank, or if there are any
     *                 errors.
     *
     */
    auto initWithCode(const std::string& vert_source,
                      const std::string& frag_source,
                      const std::string& geom_source = "",
                      const std::string& tcs_source    = "",
                      const std::string& tes_source    = "") -> pneu::core::MethodResult;

    /**
     * Returns a handle to the shader object in gpu memory.
     * @return The numerical id of the shader.
     */
    auto getShaderProgram() const -> ShaderId { return fProgramId; }

    /**
     * Binds the shader so that it is in use for the next operation.
     */
    auto bind() -> void;

    /**
     * Unbind the shader.
     */
    auto unbind() -> void;

private:
    auto _setDefaultAttributes() -> void;

    auto _compileShader(ShaderId, const std::string& shader_src) -> pneu::core::MethodResult;
    auto _linkShaderProgram() -> pneu::core::MethodResult;

    bool fBound;
    ShaderId fProgramId;
};
/*
// Used to update shaders
class ShaderUpdateMixin {
public:
    ShaderUpdateMixin(std::shared_ptr<pneu::graphics::Shader> shader)
        :
        fShader(shader) { }
    virtual ~ShaderUpdateMixin() = default;

    virtual auto update(double delta_time) -> void = 0;
    std::shared_ptr<pneu::graphics::Shader> fShader;
};
*/
} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_SHADER_HPP
