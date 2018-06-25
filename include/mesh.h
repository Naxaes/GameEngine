//
// Created by Ted Klein Bergman on 5/17/18.
//

#ifndef OPENGLPROJECT_MESH_H
#define OPENGLPROJECT_MESH_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <texture.h>
#include <shader.h>

//struct Vertex
//{
//    glm::vec3 positions;
//    glm::vec3 texture_coordinates;
//    glm::vec3 normals;
//};
//
//
//
//class Mesh
//{
//public:
//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
//    std::vector<Texture> textures;
//
//    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
//    ~Mesh();
//
//    void draw(const Shader& shader);
//private:
//    GLuint vbo, vao, ebo;
//
//    void initialize();
//};


#endif //OPENGLPROJECT_MESH_H
