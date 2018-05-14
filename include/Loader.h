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
    std::vector<GLfloat> data;
    std::vector<unsigned int> indices;
};

OBJData load_obj_file(const char* path, bool normalize = false);


#endif //OPENGLPROJECT_LOADER_H
