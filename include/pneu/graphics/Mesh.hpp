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

#ifndef PNEUMATIC_MESH_HPP
#define PNEUMATIC_MESH_HPP

#include <string>
#include <vector>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#pragma clang diagnostic pop

namespace pneu {

namespace graphics {

class Mesh final {
public:
    explicit Mesh(int num_verts = 0);

    // Constructor methods
    static auto generateTriangle() -> std::shared_ptr<Mesh>;
    static auto generateCube() -> std::shared_ptr<Mesh>;
    static auto generateSphere() -> std::shared_ptr<Mesh>;
    static auto generatePlane(float x_scale, float y_scale) -> std::shared_ptr<Mesh>;

    static auto loadFromObjFile(const std::string& file_name) -> std::shared_ptr<Mesh>;

    auto draw() -> void;

private:
    auto _generateNormals() -> void;
    auto _bufferData() -> void;

    auto _reserveArrays() -> void;

    auto _bufferVertices() -> void;
    auto _bufferNormals() -> void;
    auto _bufferColors() -> void;
    auto _bufferTexCoords() -> void;

    static auto _loadFromFile(const std::string&) -> std::shared_ptr<Mesh>;

    struct GlMeshImpl;
    std::unique_ptr<GlMeshImpl> fGlMeshImpl;
};

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_MESH_HPP
