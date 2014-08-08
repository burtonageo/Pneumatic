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

#include "graphics/RenderObject.hpp"

#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"

using namespace std;

pneu::graphics::RenderObject::RenderObject()
  :
  fShaders(),
  fTextures(),
  fShaderUpdaters(),
  fModelMatrix(glm::mat4(1.0)),
  fCurrentShaderIndex(0)
{

}

pneu::graphics::RenderObject::~RenderObject() = default;

auto
pneu::graphics::RenderObject::changeShaders()  -> void
{
  fCurrentShaderIndex++;

  if (fCurrentShaderIndex == fShaders.size()) {
    fCurrentShaderIndex = 0;
  }
}

auto
pneu::graphics::RenderObject::setShaderLight(const pneu::graphics::Light& light)  -> void
{
  // TODO: shader light
}

auto
pneu::graphics::RenderObject::addTexture(const std::string& tex_file) -> void
{
  auto tex = make_shared<pneu::graphics::Texture>();
  auto tex_init_res = tex->init(tex_file);

  if (!tex_init_res.isOk()) {
    cout << tex_init_res.getError() << endl;
    return;
  }

  fTextures.push_back(tex);
}

auto
pneu::graphics::RenderObject::getShader() const  -> std::shared_ptr<pneu::graphics::Shader>
{
  return fShaders.at(fCurrentShaderIndex);
}

auto
pneu::graphics::RenderObject::addShader(std::shared_ptr<pneu::graphics::Shader> shader)  -> void
{
  if (shader != nullptr) {
    fShaders.push_back(shader);
  }
}

auto
pneu::graphics::RenderObject::getModelMatrix() const -> glm::mat4
{
  return fModelMatrix;
}

auto
pneu::graphics::RenderObject::setModelMatrix(const glm::mat4& matrix)  -> void
{
  fModelMatrix = matrix;
}

auto
pneu::graphics::RenderObject::bindCurrentShader() -> void
{
  auto k_curr_shader = _getCurrentShader();
  if (k_curr_shader != nullptr) {
    glUseProgram(k_curr_shader->getShaderProgram());
  }
}

auto
pneu::graphics::RenderObject::bindCurrentTexture() -> void
{
  const auto k_curr_shader = _getCurrentShader();
  const auto k_curr_tex = _getCurrentTexture();

  if (k_curr_shader != nullptr && k_curr_tex != nullptr) {
    k_curr_tex->bind(k_curr_shader);
  }
}

auto
pneu::graphics::RenderObject::unBindCurrentShader() -> void
{
  glUseProgram(0);
}

auto
pneu::graphics::RenderObject::unBindCurrentTexture() -> void
{
  const auto k_curr_tex = _getCurrentTexture();
  if (k_curr_tex != nullptr) {
    k_curr_tex->unbind();
  }
}

auto
pneu::graphics::RenderObject::_getCurrentShader() -> std::shared_ptr<Shader>
{
  return fShaders.size() > 0 ? fShaders.at(fCurrentShaderIndex)
                             : nullptr;
}

auto
pneu::graphics::RenderObject::_getCurrentTexture() -> std::shared_ptr<Texture>
{
  return fTextures.size() > 0 ? fTextures.at(fCurrentShaderIndex)
                              : nullptr;
}

