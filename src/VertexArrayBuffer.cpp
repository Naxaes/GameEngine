//
// Created by Ted Klein Bergman on 3/5/18.
//

// #include <glad/glad.h>

#include "VertexArrayBuffer.h"

#include <glad/glad.h>

#include "gl_debug.h"



GLuint create_vertex_buffer(GLfloat positions[]) 
{
    unsigned int number_of_elements  = 12;

    GLuint vbo;
    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, number_of_elements * sizeof(GLfloat), positions, GL_STATIC_DRAW));

    return vbo;
}


GLuint create_index_buffer(GLuint indices[]) 
{
    unsigned int number_of_elements = 6;

    GLuint ibo;
    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, number_of_elements * sizeof(GLuint), indices, GL_STATIC_DRAW));
    
    return ibo;
}


GLuint create_array_buffer() 
{
    GLuint vao;
    GLCALL(glGenVertexArrays(1, &vao));

    return vao;
}



GLuint bind_to_vao(GLuint vao, GLuint vbo, GLuint ibo)
{
    unsigned int elements_per_vertex = 3;

    GLCALL(glBindVertexArray(vao));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, elements_per_vertex, GL_FLOAT, GL_FALSE, elements_per_vertex * sizeof(GLfloat), 0));

    return vao;
}