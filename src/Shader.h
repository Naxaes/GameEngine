//
// Created by Ted Klein Bergman on 3/6/18.
//

#ifndef OPENGLPROJECT_SHADER_H
#define OPENGLPROJECT_SHADER_H

#include <glad/glad.h>

struct ShaderSources;
enum class ShaderType;
ShaderSources load_shaders(const char* filepath);
GLuint create_shader_program(const char *filepath);


#endif //OPENGLPROJECT_SHADER_H
