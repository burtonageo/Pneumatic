/**
 * This file is part of the Pneumatic game engine
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

#include "graphics/Shader.hpp"

#include <iostream>
#include <string>
#include <vector>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

#include "core/ResourceLoader.hpp"

using namespace std;
using namespace Pneumatic::Core;

Pneumatic::Graphics::Shader::Shader()
  :
  fProgramID(0)
{

}

Pneumatic::Graphics::Shader::~Shader()
{
  glDeleteProgram(fProgramID);
}

auto
Pneumatic::Graphics::Shader::init(const std::string& vert_file,
                                  const std::string& frag_file,
                                  const std::string& geom_file,
                                  const std::string& tcs_file,
                                  const std::string& tes_file) -> Pneumatic::Core::MethodResult
{
  fProgramID = glCreateProgram();

  #define CREATE(file, file_path, id, shader_type) \
    GLuint id; \
    std::string file_path; \
    do { \
      auto tup  = _createShader(shader_type, file); \
      id        = get<0>(tup); \
      file_path = get<1>(tup); \
      \
      if (file != "" && id == 0) { \
        return MethodResult::error(string("Could not create shader from file: ") \
                                   .append(file_path)); \
      } \
    } while(0)

  CREATE(vert_file, vert_path, vert_shader_id, GL_VERTEX_SHADER);
  CREATE(frag_file, frag_path, frag_shader_id, GL_FRAGMENT_SHADER);
  CREATE(geom_file, geom_path, geom_shader_id, GL_GEOMETRY_SHADER);
  CREATE(tcs_file,  tcs_path,  tcs_shader_id,  GL_TESS_CONTROL_SHADER);
  CREATE(tes_file,  tes_path,  tes_shader_id,  GL_TESS_EVALUATION_SHADER);

  #define TRY_COMPILE(file, func) \
    do { \
      if (file != "") { \
        PNEU_TRY_METHOD(func); \
      } \
    } while(0)

  PNEU_TRY_METHOD(_compileShader(vert_shader_id, vert_path));
  PNEU_TRY_METHOD(_compileShader(frag_shader_id, frag_path));
  
  TRY_COMPILE(geom_file, _compileShader(geom_shader_id, geom_path));
  TRY_COMPILE(tcs_file,  _compileShader(tcs_shader_id,  tcs_path));
  TRY_COMPILE(tes_file,  _compileShader(tes_shader_id,  tes_path));

  PNEU_TRY_METHOD(_linkShaderProgram());

  _setDefaultAttributes();

  glDeleteShader(vert_shader_id);
  glDeleteShader(frag_shader_id);
  glDeleteShader(geom_shader_id);
  glDeleteShader(tcs_shader_id);
  glDeleteShader(tes_shader_id);

  return MethodResult::ok();
}

auto
Pneumatic::Graphics::Shader::getShaderProgram() const -> GLuint
{
  return fProgramID;
}

auto
Pneumatic::Graphics::Shader::_setDefaultAttributes() -> void
{
  const GLuint k_vertex_buffer  = 0;
  const GLuint k_color_buffer   = 1;
  const GLuint k_texture_buffer = 2;
  const GLuint k_normals_buffer = 3;

  glBindAttribLocation(fProgramID, k_vertex_buffer,  "position");
  glBindAttribLocation(fProgramID, k_color_buffer,   "color");
  glBindAttribLocation(fProgramID, k_texture_buffer, "texCoord");
  glBindAttribLocation(fProgramID, k_normals_buffer, "normal");
}

auto
Pneumatic::Graphics::Shader::_createShader(GLenum shader_type,
                                           const std::string& shader_file) -> std::pair<GLuint, std::string>
{
  if (shader_file == "") {
    return make_pair(0, "");
  }

  std::string path, suffix;
  switch (shader_type) {
    case GL_VERTEX_SHADER:
      //path = Config::getVertexDir();
      suffix = ".vert_glsl";
      break;
    case GL_FRAGMENT_SHADER:
      //path = Config::getFragmentDir();
      suffix = ".frag_glsl";
      break;
    case GL_GEOMETRY_SHADER:
      //path = Config::getGeometryDir();
      suffix = ".geom_glsl";
      break;
    case GL_TESS_CONTROL_SHADER:
      //path = Config::getTessCtrlDir();
      suffix = ".tcs_glsl";
      break;
    case GL_TESS_EVALUATION_SHADER:
      //path = Config::getTessEvalDir();
      suffix = ".tes_glsl";
      break;
    default:
      return make_pair(0, "");
  }

  GLuint shader_id = glCreateShader(shader_type);

  return make_pair(shader_id, path + shader_file + suffix);
}

auto
Pneumatic::Graphics::Shader::_compileShader(GLuint shader_id,
                                            const std::string& shader_path) -> Pneumatic::Core::MethodResult
{
  auto source_result = ResourceLoader::loadTextFile(shader_path);

  if (!source_result.isOk()) {
    return MethodResult::error(source_result.getError());
  }
  
  const auto source_str = source_result.get();
  const auto* k_source_ptr = source_str.c_str();

  glShaderSource(shader_id, 1, &k_source_ptr , NULL);
  glCompileShader(shader_id);

  GLint result;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

  if (result == GL_FALSE) {
    int info_log_length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

    std::vector<char> error_msg_vec(info_log_length);
    glGetShaderInfoLog(shader_id, info_log_length, NULL, error_msg_vec.data());

    return MethodResult::error(string(error_msg_vec.begin(),
                                    error_msg_vec.end()));
  }

  glAttachShader(fProgramID, shader_id);
  return MethodResult::ok();
}

auto
Pneumatic::Graphics::Shader::_linkShaderProgram() -> Pneumatic::Core::MethodResult
{
  glLinkProgram(fProgramID);

  GLint result;
  glGetProgramiv(fProgramID, GL_LINK_STATUS, &result);

  if (result == GL_FALSE) {
    int info_log_length;
    glGetProgramiv(fProgramID, GL_INFO_LOG_LENGTH, &info_log_length);

    std::vector<char> error_msg_vec(max(info_log_length, 1));
    glGetProgramInfoLog(fProgramID, info_log_length, NULL, error_msg_vec.data());

    return MethodResult::error(string(error_msg_vec.begin(),
                                    error_msg_vec.end()));
  }
  return MethodResult::ok();
}
