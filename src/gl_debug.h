//
// Created by Ted Klein Bergman on 1/19/18.
//

#ifndef OPENGLPROJECT_GL_DEBUG_H
#define OPENGLPROJECT_GL_DEBUG_H

#include "glad/glad.h"

#define GLCALL(x) clear_errors(); x; print_errors(#x, __FILE__, __LINE__)
#define check_shader_status(shaderID, status) _check_shader_status(shaderID, status, #status)
#define check_program_status(programID, status) _check_program_status(programID, status, #status)

const char* error_to_string(GLuint error);
void clear_errors();

void print_errors(const char* function_name, const char* file_name, int line);
bool _check_shader_status(GLuint shaderID, GLuint status, const char* status_name);
bool _check_program_status(GLuint programID, GLuint status, const char* status_name);

#endif // OPENGLPROJECT_GL_DEBUG_H
