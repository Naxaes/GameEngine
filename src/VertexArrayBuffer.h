//
// Created by Ted Klein Bergman on 3/5/18.
//

#ifndef OPENGLPROJECT_VERTEXARRAYBUFFER_H
#define OPENGLPROJECT_VERTEXARRAYBUFFER_H

#include <glad/glad.h>

#include <vector>

#include "gl_debug.h"

GLuint create_vertex_buffer(GLfloat positions[], unsigned int count, unsigned int mode = GL_STATIC_DRAW);
GLuint create_index_buffer(GLuint indices[], unsigned int count, unsigned int mode = GL_STATIC_DRAW);
GLuint create_array_buffer();
void bind_to_vao(GLuint vao, GLuint vbo, GLuint ibo, unsigned char count_per_vertex);


template <typename T>
class VertexBuffer
{
public:
    GLuint id{};

    VertexBuffer(T data[], unsigned int count, unsigned int mode = GL_STATIC_DRAW)
    {
        GLCALL(glGenBuffers(1, &id));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, mode));
    }

    void bind() const
    {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
    }

};


class IndexBuffer
{
public:
    GLuint id{};

    IndexBuffer(GLuint data[], unsigned int count, unsigned int mode = GL_STATIC_DRAW)
    {
        GLCALL(glGenBuffers(1, &id));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, mode));
    }

    void bind() const
    {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    }

};


class VertexBufferElement
{
public:
    VertexBufferElement(unsigned int count, unsigned int offset, GLuint type, GLboolean normalized)
            : count(count), offset(offset), type(type), normalized(normalized) {}
    unsigned int count;
    unsigned int offset;
    GLuint type;
    GLboolean normalized;
};


class VertexBufferLayout
{
public:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;

    template <typename T>
    void push(unsigned int count, GLboolean normalized = GL_FALSE);

};

class VertexArray
{
public:
    GLuint id{};
    unsigned int count{};

    VertexArray()
    {
        GLCALL(glGenVertexArrays(1, &id));
    }

    void bind()
    {
        GLCALL(glBindVertexArray(id));
    }

    template <typename T>
    void add_buffer(const VertexBuffer<T>& buffer, const VertexBufferLayout& layout)
    {
        bind();
        buffer.bind();

        unsigned int offset = 0;
        for (unsigned int i = 0; i < layout.elements.size(); i++)
        {
            const VertexBufferElement& element = layout.elements[i];
            GLCALL(glEnableVertexAttribArray(i));
            GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride, (void*)offset));

            offset += element.offset;
        }
    }

    template <typename T>
    void add_buffer(const VertexBuffer<T>& buffer, const IndexBuffer& ibo, const VertexBufferLayout& layout)
    {
        add_buffer(buffer, layout);
        ibo.bind();
    }

};


#endif //OPENGLPROJECT_VERTEXARRAYBUFFER_H
