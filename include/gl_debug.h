//
// Created by Ted Klein Bergman on 1/19/18.
//

#ifndef OPENGLPROJECT_GL_DEBUG_H
#define OPENGLPROJECT_GL_DEBUG_H

#include "glad/glad.h"

#define GLCALL(x) clear_errors(); x; print_errors(#x, __FILE__, __LINE__)

const char* error_to_string(GLuint error);
void clear_errors();

void print_errors(const char* function_name, const char* file_name, int line);

#endif // OPENGLPROJECT_GL_DEBUG_H
