//
// Created by Ted Klein Bergman on 3/6/18.
//

#ifndef OPENGLPROJECT_LOADER_H
#define OPENGLPROJECT_LOADER_H

#include <vector>
#include <glad/glad.h>

#include "glm/glm.hpp"


struct OBJData
{
    std::vector<GLfloat> positions;
    std::vector<GLfloat> texture_coordinates;
    std::vector<GLfloat> normals;
    std::vector<unsigned int> indices;
};

OBJData load_obj_file(const char* path);


#endif //OPENGLPROJECT_LOADER_H
