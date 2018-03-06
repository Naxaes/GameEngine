//
// Created by Ted Klein Bergman on 3/5/18.
//

// #include <glad/glad.h>

#include "VertexArrayBuffer.h"

#include <glad/glad.h>

#include "gl_debug.h"



GLuint create_vertex_buffer(GLfloat positions[], unsigned int count, unsigned int mode)
{
    GLuint vbo;
    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), positions, mode));

    return vbo;
}


GLuint create_index_buffer(GLuint indices[], unsigned int count, unsigned int mode)
{
    GLuint ibo;
    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, mode));
    
    return ibo;
}


GLuint create_array_buffer() 
{
    GLuint vao;
    GLCALL(glGenVertexArrays(1, &vao));

    return vao;
}



void bind_to_vao(GLuint vao, GLuint vbo, GLuint ibo, unsigned char count_per_vertex)
{
    ASSERT(count_per_vertex > 0 && count_per_vertex <= 4, "Count per vertex must be between 1 and 4.");

    GLCALL(glBindVertexArray(vao));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, count_per_vertex, GL_FLOAT, GL_FALSE, count_per_vertex * sizeof(GLfloat), 0));
}