//
// Created by Ted Klein Bergman on 3/5/18.
//

// #include <glad/glad.h>

#include "VertexArrayBuffer.h"

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
    unsigned int offset = stride;
    elements.push_back({vbo, index++, count, GL_FLOAT, normalize, offset});
    stride += sizeof(GLfloat) * count;
}

template <>
void VertexBufferLayout::push<GLuint>(VertexBuffer vbo, unsigned int count, GLboolean normalize)
{
    unsigned int offset = stride;
    elements.push_back({vbo, index++, count, GL_UNSIGNED_INT, normalize, offset});
    stride += sizeof(GLuint) * count;
}

template <>
void VertexBufferLayout::push<GLint>(VertexBuffer vbo, unsigned int count, GLboolean normalize)
{
    unsigned int offset = stride;
    elements.push_back({vbo, index++, count, GL_INT, normalize, offset});
    stride += sizeof(GLint) * count;
}