/**
 * This file is part of the pneu game engine
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

#include "pneu/graphics/Shader.hpp"

#include "pneu/core/ResourceLoader.hpp"
#include "pneu/core/FuncResult.hpp"

#include <iostream>
#include <string>
#include <vector>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

static inline auto
_getShaderFileSuffix(GLenum shader_type) -> pneu::core::FuncResult<std::string>
{
  switch (shader_type) {
    case GL_VERTEX_SHADER:
      return pneu::core::FuncResult<std::string>::ok(".vert_glsl");;
    case GL_FRAGMENT_SHADER:
      return pneu::core::FuncResult<std::string>::ok(".frag_glsl");
    case GL_GEOMETRY_SHADER:
      return pneu::core::FuncResult<std::string>::ok(".geom_glsl");
    case GL_TESS_CONTROL_SHADER:
      return pneu::core::FuncResult<std::string>::ok(".tcs_glsl");
    case GL_TESS_EVALUATION_SHADER:
      return pneu::core::FuncResult<std::string>::ok(".tes_glsl");
    default:
      return pneu::core::FuncResult<std::string>::error("Invalid shader type");
  }
}

pneu::graphics::Shader::Shader()
  :
  fProgramId(0)
{

}

pneu::graphics::Shader::~Shader()
{
  glDeleteProgram(fProgramId);
}

auto
pneu::graphics::Shader::loadFromFile(const std::string& vert_file,
                                     const std::string& frag_file,
                                     const std::string& geom_file,
                                     const std::string& tcs_file,
                                     const std::string& tes_file) -> pneu::core::MethodResult
{
  #define CREATE_PATH(file_path, file, shader_type) \
    std::string file_path; \
    do { \
      auto suffix = _getShaderFileSuffix(shader_type); \
      if (!suffix.isOk()) { \
        return pneu::core::MethodResult::error(suffix.getError()); \
      } \
      file_path = file + suffix.get(); \
    } while(0)

  CREATE_PATH(vert_path, vert_file, GL_VERTEX_SHADER);
  CREATE_PATH(frag_path, frag_file, GL_FRAGMENT_SHADER);
  CREATE_PATH(geom_path, geom_file, GL_GEOMETRY_SHADER);
  CREATE_PATH(tcs_path,  tcs_file,  GL_TESS_CONTROL_SHADER);
  CREATE_PATH(tes_path,  tes_file,  GL_TESS_EVALUATION_SHADER);

  #define LOAD_SHADER_FILE(var_name, shader_path) \
    std::string var_name; \
    do { \
      auto source_result = pneu::core::ResourceLoader::loadTextFile(shader_path); \
      if (source_result.isOk()) { \
        var_name = source_result.get(); \
      } else { \
        return pneu::core::MethodResult::error(source_result.getError()); \
      } \
    } while(0)

  LOAD_SHADER_FILE(vert_source, vert_path);
  LOAD_SHADER_FILE(frag_source, frag_path);
  LOAD_SHADER_FILE(geom_source, geom_path);
  LOAD_SHADER_FILE(tcs_source,  tcs_path);
  LOAD_SHADER_FILE(tes_source,  tes_path);

  return initWithCode(vert_source, frag_source, geom_source, tcs_source, tes_source);
}

auto
pneu::graphics::Shader::initWithCode(const std::string& vert_source,
                                     const std::string& frag_source,
                                     const std::string& geom_source,
                                     const std::string& tcs_source,
                                     const std::string& tes_source) -> pneu::core::MethodResult
{
  fProgramId = glCreateProgram();

  #define TRY_CREATE_SHADER(shader_source, shader_id, shader_type) \
    ShaderId shader_id = 0; \
    do { \
      if (shader_source != "") { \
        shader_id = glCreateShader(shader_type); \
        if (shader_id == 0) { \
          return pneu::core::MethodResult::error("Cannot create shader of type"); \
        } \
      } \
    } while(0)

  TRY_CREATE_SHADER(vert_source, vert_shader_id, GL_VERTEX_SHADER);
  TRY_CREATE_SHADER(frag_source, frag_shader_id, GL_FRAGMENT_SHADER);
  TRY_CREATE_SHADER(geom_source, geom_shader_id, GL_GEOMETRY_SHADER);
  TRY_CREATE_SHADER(tes_source,  tes_shader_id,  GL_TESS_CONTROL_SHADER);
  TRY_CREATE_SHADER(tcs_source,  tcs_shader_id,  GL_TESS_EVALUATION_SHADER);

  PNEU_TRY_METHOD(_compileShader(vert_shader_id, vert_source));
  PNEU_TRY_METHOD(_compileShader(frag_shader_id, frag_source));
  PNEU_TRY_METHOD(_compileShader(geom_shader_id, geom_source));
  PNEU_TRY_METHOD(_compileShader(tes_shader_id,  tcs_source));
  PNEU_TRY_METHOD(_compileShader(tcs_shader_id,  tes_source));

  PNEU_TRY_METHOD(_linkShaderProgram());

  _setDefaultAttributes();

  glDeleteShader(vert_shader_id);
  glDeleteShader(frag_shader_id);
  glDeleteShader(geom_shader_id);
  glDeleteShader(tcs_shader_id);
  glDeleteShader(tes_shader_id);

  return pneu::core::MethodResult::ok();
}

auto
pneu::graphics::Shader::getShaderProgram() const -> ShaderId
{
  return fProgramId;
}

auto
pneu::graphics::Shader::bind() -> void
{
  glUseProgram(fProgramId);
}

auto
pneu::graphics::Shader::unbind() -> void
{
  glUseProgram(0);
}

auto
pneu::graphics::Shader::_setDefaultAttributes() -> void
{
  const ShaderId k_vertex_buffer  = 0;
  const ShaderId k_color_buffer   = 1;
  const ShaderId k_texture_buffer = 2;
  const ShaderId k_normals_buffer = 3;

  glBindAttribLocation(fProgramId, k_vertex_buffer,  "position");
  glBindAttribLocation(fProgramId, k_color_buffer,   "color");
  glBindAttribLocation(fProgramId, k_texture_buffer, "texCoord");
  glBindAttribLocation(fProgramId, k_normals_buffer, "normal");
}

auto
pneu::graphics::Shader::_compileShader(ShaderId shader_id,
                                       const std::string& shader_src) -> pneu::core::MethodResult
{
  if (shader_src == "") {
    return pneu::core::MethodResult::ok();
  }

  const auto* k_source_ptr = shader_src.c_str();

  glShaderSource(shader_id, 1, &k_source_ptr , NULL);
  glCompileShader(shader_id);

  GLint result;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

  if (result == GL_FALSE) {
    int info_log_length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

    std::vector<char> error_msg_vec(info_log_length);
    glGetShaderInfoLog(shader_id, info_log_length, NULL, error_msg_vec.data());

    return pneu::core::MethodResult::error(std::string(error_msg_vec.begin(),
                                                       error_msg_vec.end()));
  }

  glAttachShader(fProgramId, shader_id);
  return pneu::core::MethodResult::ok();
}

auto
pneu::graphics::Shader::_linkShaderProgram() -> pneu::core::MethodResult
{
  glLinkProgram(fProgramId);

  GLint result;
  glGetProgramiv(fProgramId, GL_LINK_STATUS, &result);

  if (result == GL_FALSE) {
    int info_log_length;
    glGetProgramiv(fProgramId, GL_INFO_LOG_LENGTH, &info_log_length);

    std::vector<char> error_msg_vec(std::max(info_log_length, 1));
    glGetProgramInfoLog(fProgramId, info_log_length, NULL, error_msg_vec.data());

    return pneu::core::MethodResult::error(std::string(error_msg_vec.begin(),
                                                       error_msg_vec.end()));
  }
  return pneu::core:: MethodResult::ok();
}
