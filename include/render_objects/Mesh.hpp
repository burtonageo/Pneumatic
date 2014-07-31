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

#pragma once

#ifndef PNEUMATIC_MESH_HPP
#define PNEUMATIC_MESH_HPP

#include <string>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "GlInclude.hpp"

namespace Pneumatic {

namespace Graphics {

class Mesh final {
public:
  explicit Mesh(int num_verts = 0);
  ~Mesh(void);

  // Constructor methods
  static auto generateTriangle(void)                        -> std::shared_ptr<Mesh>;
  static auto generateCube(void)                            -> std::shared_ptr<Mesh>;
  static auto generateSphere(void)                          -> std::shared_ptr<Mesh>;
  static auto generatePlane(float x_scale, float y_scale)   -> std::shared_ptr<Mesh>;

  static auto loadFromObjFile(const std::string& file_name) -> std::shared_ptr<Mesh>;

  auto draw(void)                                           -> void;

private:
  auto _generateNormals(void)                               -> void;
  auto _bufferData(void)                                    -> void;

  auto _reserveArrays(void)                                 -> void;

  auto _bufferVertices(void)                                -> void;
  auto _bufferNormals(void)                                 -> void;
  auto _bufferColors(void)                                  -> void;
  auto _bufferTexCoords(void)                               -> void;

  static auto _loadFromFile(const std::string&)             -> std::shared_ptr<Mesh>;

  std::vector<glm::vec3> fVertices, fNormals;
  std::vector<glm::vec4> fColors;
  std::vector<glm::vec2> fTexCoords;

  int fNumVertices;

  GLuint fVao, fType;
};

} // namespace Graphics

} // namespace Pneumatic

#endif // PNEUMATIC_MESH_HPP
