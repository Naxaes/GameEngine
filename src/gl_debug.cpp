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
            unsigned int size = 100;
            char temp_message[size];
            snprintf(temp_message, size, "UNKNOWN ERROR %d", error);
            error_message = temp_message;
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