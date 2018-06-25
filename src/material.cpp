//
// Created by Ted Klein Bergman on 3/28/18.
//

#include "material.h"

void Material::load(const Shader& program, const std::string& name)
{
    program.bind_uniform((name + ".ambient").c_str(),   ambient.x,  ambient.y,  ambient.z);
    program.bind_uniform((name + ".diffuse").c_str(),   diffuse.x,  diffuse.y,  diffuse.z);
    program.bind_uniform((name + ".specular").c_str(),  specular.x, specular.y, specular.z);
    program.bind_uniform((name + ".shininess").c_str(), shininess);
}


std::array<std::string, 4> Material::string_representation(const std::string& name)
{
    std::array<std::string, 4> result;
    unsigned int index = 0;

    const char* attributes[] = {"ambient", "diffuse", "specular", "shininess"};
    for (const char* attribute : attributes)
    {
        result[index++] = std::string(name) + "." + attribute;
    }

    return result;
};