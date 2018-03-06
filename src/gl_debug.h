//
// Created by Ted Klein Bergman on 1/19/18.
//

#ifndef GL_DEBUG_H
#define GL_DEBUG_H

#include "glad/glad.h"

#define GLCALL(x) clear_errors(); x; print_errors(#x, __FILE__, __LINE__)
#define check_shader_status(shaderID, status) _check_shader_status(shaderID, status, #status)
#define check_program_status(programID, status) _check_program_status(programID, status, #status)
#define ASSERT(condition, message) _assertion(condition, message, #condition, __FILE__, __LINE__)

const char* error_to_string(GLuint error);
void clear_errors();

void print_errors(const char* function_name, const char* file_name, int line);
bool _check_shader_status(GLuint shaderID, GLuint status, const char* status_name);
bool _check_program_status(GLuint programID, GLuint status, const char* status_name);
void _assertion(bool condition, const char* message, const char* condition_string, const char* file_name, int line);

#endif // GL_DEBUG_H
