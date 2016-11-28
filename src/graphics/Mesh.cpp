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

#include "pneu/graphics/Mesh.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma clang diagnostic pop

#include "pneu/core/ResourceLoader.hpp"
#include "pneu/graphics/Shader.hpp"

namespace pneu {

namespace graphics {

struct Mesh::GlMeshImpl {
    GlMeshImpl(int num_verts, GLuint type)
        :
        fNumVertices(num_verts),
        fVao(0),
        fType(type),
        fVertices(),
        fNormals(),
        fColors(),
        fTexCoords() { }

    int fNumVertices;

    GLuint fVao, fType;

    std::vector<glm::vec3> fVertices, fNormals;
    std::vector<glm::vec4> fColors;
    std::vector<glm::vec2> fTexCoords;

};

} // namespace graphics

} // namespace pneu

pneu::graphics::Mesh::Mesh(int num_verts)
    :
    fGlMeshImpl(std::make_unique<GlMeshImpl>(num_verts, GL_TRIANGLES))
{

}

auto
pneu::graphics::Mesh::generateTriangle() -> std::shared_ptr<Mesh>
{
    auto mesh = std::make_shared<Mesh>(3);
    mesh->_reserveArrays();

    mesh->fGlMeshImpl->fVertices = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3( 1.0f, -1.0f, 0.0f),
        glm::vec3( 0.0f,    1.0f, 0.0f),
    };

    mesh->fGlMeshImpl->fColors = {
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    };

    mesh->fGlMeshImpl->fTexCoords = {
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
    };

    mesh->_bufferData();
    return mesh;
}

auto
pneu::graphics::Mesh::generateCube() -> std::shared_ptr<Mesh>
{
    auto mesh = _loadFromFile("cube");
    mesh->_generateNormals();
    mesh->_bufferData();
    return mesh;
}

auto
pneu::graphics::Mesh::generateSphere() -> std::shared_ptr<Mesh>
{
    return nullptr;
}

auto
pneu::graphics::Mesh::loadFromObjFile(const std::string& file_name) -> std::shared_ptr<Mesh>
{
    return nullptr;
}

auto
pneu::graphics::Mesh::_loadFromFile(const std::string& file_name) -> std::shared_ptr<Mesh>
{
    // TODO: make asset directories
    std::string file_path = file_name + ".mesh";
    std::ifstream fs(file_path);

    if (!fs) {
        return nullptr;
    }

    auto mesh = std::make_shared<Mesh>();
    fs >> mesh->fGlMeshImpl->fNumVertices;

    mesh->_reserveArrays();

    int has_tex = 0, has_color = 0;
    fs >> has_tex;
    fs >> has_color;

    for (int i = 0; i < mesh->fGlMeshImpl->fNumVertices; i++) {
        fs >> mesh->fGlMeshImpl->fVertices[i].x;
        fs >> mesh->fGlMeshImpl->fVertices[i].y;
        fs >> mesh->fGlMeshImpl->fVertices[i].z;
    }
    mesh->fGlMeshImpl->fVertices.shrink_to_fit();

    if (has_color) {
        for (int i = 0; i < mesh->fGlMeshImpl->fNumVertices; i++) {
            fs >> mesh->fGlMeshImpl->fColors[i].r;
            fs >> mesh->fGlMeshImpl->fColors[i].g;
            fs >> mesh->fGlMeshImpl->fColors[i].b;
            fs >> mesh->fGlMeshImpl->fColors[i].a;
        }
    }
    mesh->fGlMeshImpl->fColors.shrink_to_fit();

    if (has_tex) {
        for (int i = 0; i < mesh->fGlMeshImpl->fNumVertices; i++) {
            fs >> mesh->fGlMeshImpl->fTexCoords[i].x;
            fs >> mesh->fGlMeshImpl->fTexCoords[i].y;
        }
    }
    mesh->fGlMeshImpl->fTexCoords.shrink_to_fit();

    return mesh;
}

auto
pneu::graphics::Mesh::draw() -> void
{
    glBindVertexArray(fGlMeshImpl->fVao);
    glDrawElements(fGlMeshImpl->fType, fGlMeshImpl->fNumVertices, GL_UNSIGNED_INT, 0);
    glDrawArrays(fGlMeshImpl->fType, 0, fGlMeshImpl->fNumVertices * sizeof(glm::vec3));
    glBindVertexArray(0);
}

auto
pneu::graphics::Mesh::_generateNormals() -> void
{
    for (int i = 0; i < fGlMeshImpl->fNumVertices; i+=3) {
        glm::vec3& a = fGlMeshImpl->fVertices[i];
        glm::vec3& b = fGlMeshImpl->fVertices[i+1];
        glm::vec3& c = fGlMeshImpl->fVertices[i+2];

        glm::vec3 normal = glm::cross(b - a, c - a);
        glm::normalize(normal);

        fGlMeshImpl->fNormals[i]     = normal;
        fGlMeshImpl->fNormals[i+1] = normal;
        fGlMeshImpl->fNormals[i+2] = normal;
    }
    fGlMeshImpl->fNormals.shrink_to_fit();
}

auto
pneu::graphics::Mesh::_bufferData() -> void
{
    glGenVertexArrays(1, &fGlMeshImpl->fVao);
    glBindVertexArray(fGlMeshImpl->fVao);

    _bufferVertices();
    _bufferColors();
    _bufferTexCoords();
    _bufferNormals();

    glBindVertexArray(0);
}

auto
pneu::graphics::Mesh::_reserveArrays() -> void
{
    fGlMeshImpl->fVertices    = std::vector<glm::vec3>(fGlMeshImpl->fNumVertices, glm::vec3());
    fGlMeshImpl->fNormals     = std::vector<glm::vec3>(fGlMeshImpl->fNumVertices, glm::vec3());
    fGlMeshImpl->fColors        = std::vector<glm::vec4>(fGlMeshImpl->fNumVertices, glm::vec4());
    fGlMeshImpl->fTexCoords = std::vector<glm::vec2>(fGlMeshImpl->fNumVertices, glm::vec2());
}

#define MESH_BUFFER_DATA_METH_DECL(meth_name, member_arr, idx, vec_tp, vec_num_elems) \
    auto \
    pneu::graphics::Mesh::meth_name() -> void \
    { \
        if (fGlMeshImpl->member_arr.empty()) { \
            return; \
        } \
        \
        GLuint vbo; \
        \
        glGenBuffers(1, &vbo); \
        glBindBuffer(GL_ARRAY_BUFFER, vbo); \
        \
        glBufferData(GL_ARRAY_BUFFER, \
                                 fGlMeshImpl->fNumVertices * sizeof(vec_tp), \
                                 fGlMeshImpl->member_arr.data(),    GL_STATIC_DRAW); \
        glVertexAttribPointer(idx, vec_num_elems, GL_FLOAT, GL_FALSE, 0, 0); \
        glEnableVertexAttribArray(idx); \
    }

MESH_BUFFER_DATA_METH_DECL(_bufferVertices,  fVertices,  0, glm::vec3, 3)
MESH_BUFFER_DATA_METH_DECL(_bufferColors,    fColors,    1, glm::vec4, 4)
MESH_BUFFER_DATA_METH_DECL(_bufferTexCoords, fTexCoords, 2, glm::vec2, 2)
MESH_BUFFER_DATA_METH_DECL(_bufferNormals,   fNormals,   3, glm::vec3, 3)

#undef MESH_BUFFER_DATA_METH_DECL
