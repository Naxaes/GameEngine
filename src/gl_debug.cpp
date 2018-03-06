//
// Created by Ted Klein Bergman on 3/6/18.
//

#include "gl_debug.h"

#include <iostream>


#define GET_VARIABLE_NAME(x) #x

const char* error_to_string(GLuint error)
{
    const char* error_message;

    switch (error)
    {
        case GL_INVALID_ENUM:
            error_message = GET_VARIABLE_NAME(GL_INVALID_ENUM);
            break;
        case GL_INVALID_VALUE:
            error_message = GET_VARIABLE_NAME(GL_INVALID_VALUE);
            break;
        case GL_INVALID_OPERATION:
            error_message = GET_VARIABLE_NAME(GL_INVALID_OPERATION);
            break;
        case GL_STACK_OVERFLOW:
            error_message = GET_VARIABLE_NAME(GL_STACK_OVERFLOW);
            break;
        case GL_STACK_UNDERFLOW:
            error_message = GET_VARIABLE_NAME(GL_STACK_UNDERFLOW);
            break;
        case GL_OUT_OF_MEMORY:
            error_message = GET_VARIABLE_NAME(GL_OUT_OF_MEMORY);
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error_message = GET_VARIABLE_NAME(GL_INVALID_FRAMEBUFFER_OPERATION);
            break;
        default:
            error_message = "UNKNOWN_ERROR";
    }

    return error_message;
}


void clear_errors()
{
    while (glGetError() != GL_NO_ERROR);
}


void print_errors(const char* function_name, const char* file_name, int line)
{
    GLuint error;

    while ((error = glGetError()) != GL_NO_ERROR)
    {
        fprintf(
                stderr,
                "[OpenGL Error] (%s %i):\n\tFunction: %s\n\tFile:     %s\n\tLine:     %i\n",
                error_to_string(error), error, function_name, file_name, line
        );
        exit(-1);
    }
}


bool _check_shader_status(GLuint shaderID, GLuint status, const char* status_name)
{
    int success = 0;

    GLCALL(GLCALL(glGetShaderiv(shaderID, status, &success)));

    if (!success)
    {
        int log_size;

        GLCALL(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &log_size));

        char log[log_size];

        GLCALL(glGetShaderInfoLog(shaderID, log_size, nullptr, log));

        std::string formatted_log;

        formatted_log.push_back('\t');
        for (const char character : log)
        {
            formatted_log.push_back(character);
            if (character == '\n') {
                formatted_log.push_back('\t');
            }
        }

        fprintf(
                stderr,
                "[Shader Error] (ID %i, %s):\n%s\n",
                shaderID, status_name, formatted_log.c_str()
        );

        return false;
    }

    return true;
}


bool _check_program_status(GLuint programID, GLuint status, const char* status_name)
{
    int success = 0;

    GLCALL(glGetProgramiv(programID, status, &success));

    if (!success) {
        int log_size;

        GLCALL(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &log_size));

        char log[log_size];

        GLCALL(glGetProgramInfoLog(programID, log_size, nullptr, log));

        std::string formatted_log;

        formatted_log.push_back('\t');
        for (const char character : log) {
            formatted_log.push_back(character);
            if (character == '\n') {
                formatted_log.push_back('\t');
            }
        }

        fprintf(
                stderr,
                "[Shader Program Error] (ID %i, %s):\n%s\n",
                programID, status_name, formatted_log.c_str()
        );

        return false;
    }

    return true;
}