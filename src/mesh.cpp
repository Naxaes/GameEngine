//
// Created by Ted Klein Bergman on 5/17/18.
//

#include <mesh.h>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
    this->vertices = std::move(vertices);
    this->indices  = std::move(indices);
    this->textures = std::move(textures);

    initialize();
}

Mesh::~Mesh()
{

}

void Mesh::draw(const Shader& shader)
{

}

void Mesh::initialize()
{

}