//
// Created by Ted Klein Bergman on 3/5/18.
//

// #include <glad/glad.h>

#include "vertex_array_buffer.h"

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &id));
}
void VertexArray::bind() const
{
    GLCALL(glBindVertexArray(id));
}


template <>
void VertexBufferLayout::push<GLfloat>(VertexBuffer vbo, unsigned int count, GLboolean normalize)
{
    push(GL_FLOAT, vbo, count, normalize);
}

template <>
void VertexBufferLayout::push<GLuint>(VertexBuffer vbo, unsigned int count, GLboolean normalize)
{
    push(GL_UNSIGNED_INT, vbo, count, normalize);
}

template <>
void VertexBufferLayout::push<GLint>(VertexBuffer vbo, unsigned int count, GLboolean normalize)
{
    push(GL_INT, vbo, count, normalize);
}

void VertexBufferLayout::push(unsigned int type, VertexBuffer vbo, unsigned int count, GLboolean normalize)
{
    unsigned int offset = stride;
    elements.push_back({vbo, index, count, type, normalize, offset});
    index  += 1;
    stride += sizeof(GLint) * count;
}