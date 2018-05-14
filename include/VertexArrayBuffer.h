//
// Created by Ted Klein Bergman on 3/5/18.
//

#ifndef OPENGLPROJECT_VERTEXARRAYBUFFER_H
#define OPENGLPROJECT_VERTEXARRAYBUFFER_H

#include <glad/glad.h>

#include <vector>

#include "gl_debug.h"


class VertexBuffer
{
public:
    GLuint id{};

    template <typename T>
    static VertexBuffer* create(const T data[], unsigned int count, unsigned int mode = GL_STATIC_DRAW)
    {
        GLuint id;
        GLCALL(glGenBuffers(1, &id));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, mode));

        return new VertexBuffer(id);
    }

    template <typename T>
    static VertexBuffer* create(
            const std::vector<T>& vertices, const std::vector<T>& texture_coords, const std::vector<T>& normals, unsigned int mode = GL_STATIC_DRAW
    )
    {

        unsigned long total_count  = vertices.size() + texture_coords.size() + normals.size();
        unsigned long vertex_count = vertices.size() / 3;

        std::vector<T> data;
        data.reserve(total_count);

        unsigned int vi = 0, ti = 0, ni = 0;

        for (unsigned int i = 0; i < vertex_count; i ++)
        {
            data[i] = vertices[vi++];
            data[i] = vertices[vi++];
            data[i] = vertices[vi++];

            data[i] = texture_coords[ti++];
            data[i] = texture_coords[ti++];

            data[i] = normals[ni++];
            data[i] = normals[ni++];
            data[i] = normals[ni++];
        }

        GLuint id;
        GLCALL(glGenBuffers(1, &id));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, total_count * sizeof(T), &data[0], mode));

        return new VertexBuffer(id);
    }

    template <typename T>
    static VertexBuffer* create(const std::vector<T>& data, unsigned int mode = GL_STATIC_DRAW)
    {
        return VertexBuffer::create(&data[0], (unsigned int)data.size(), mode);
    }

    explicit VertexBuffer(GLuint id) : id(id) {}

    void bind() const
    {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
    }

};


class IndexBuffer
{
public:
    GLuint id{};

    template <typename T>
    static IndexBuffer* create(const T data[], unsigned int count, unsigned int mode = GL_STATIC_DRAW)
    {
        GLuint id;
        GLCALL(glGenBuffers(1, &id));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data, mode));

        return new IndexBuffer(id);
    }

    template <typename T>
    static IndexBuffer* create(const std::vector<T>& data, unsigned int mode = GL_STATIC_DRAW)
    {
        return IndexBuffer::create(&data[0], (unsigned int)data.size(), mode);
    }

    explicit IndexBuffer(GLuint id) : id(id) {}

    void bind() const
    {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    }

};


struct VertexBufferElement
{
    VertexBuffer vbo;
    unsigned int index;
    unsigned int count;
    GLuint type;
    GLboolean normalize;
    unsigned int offset;
};


class VertexBufferLayout
{
    unsigned int index{0u};
public:
    std::vector<VertexBufferElement> elements;
    unsigned int stride{0u};

    template <typename T>
    void push(VertexBuffer vbo, unsigned int count, GLboolean normalize = GL_FALSE);

};

class VertexArray
{
public:
    GLuint id{};

    VertexArray();
    void bind() const;

    void add_buffer(const VertexBufferLayout& layout)
    {
        bind();

        for (const VertexBufferElement& element : layout.elements)
        {
            element.vbo.bind();

            GLCALL(glEnableVertexAttribArray(element.index));
            GLCALL(glVertexAttribPointer(
                    element.index, element.count, element.type, element.normalize, layout.stride, (void*)element.offset
            ));
        }

    }

    void add_buffer(const IndexBuffer& ibo, const VertexBufferLayout& layout)
    {
        bind();
        ibo.bind();

        for (const VertexBufferElement& element : layout.elements)
        {
            element.vbo.bind();

            GLCALL(glEnableVertexAttribArray(element.index));
            GLCALL(glVertexAttribPointer(
                    element.index, element.count, element.type, element.normalize, layout.stride, (void*)element.offset
            ));
        }
    }

};


#endif //OPENGLPROJECT_VERTEXARRAYBUFFER_H
