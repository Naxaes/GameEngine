//
// Created by Ted Klein Bergman on 3/28/18.
//

#ifndef OPENGLPROJECT_MATERIAL_H
#define OPENGLPROJECT_MATERIAL_H


#include <string>
#include <array>

#include <glm/glm.hpp>

#include "shader.h"


class Material
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    ~Material() = default;
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
            ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

    std::array<std::string, 4> string_representation(const std::string& name);
    void load(const Shader& program, const std::string& name);

};


#endif //OPENGLPROJECT_MATERIAL_H
