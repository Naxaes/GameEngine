//
// Created by Ted Klein Bergman on 3/29/18.
//

#ifndef OPENGLPROJECT_MODEL_H
#define OPENGLPROJECT_MODEL_H


#include "VertexArrayBuffer.h"
#include "Loader.h"

class Model
{
private:

    VertexArray init(OBJData data)
    {
        VertexArray vao;

        VertexBuffer* vbo_data = VertexBuffer::create<GLfloat>(data.data);
        IndexBuffer*  ibo = IndexBuffer::create<GLuint>(data.indices);

        VertexBufferLayout layout;
        layout.push<GLfloat>(*vbo_data, 3);
        layout.push<GLfloat>(*vbo_data, 2);
        layout.push<GLfloat>(*vbo_data, 3);

        vao.add_buffer(*ibo, layout);

        return vao;
    }


public:

    const unsigned int vertex_count;
    const VertexArray vao;

    explicit Model(const OBJData& data) : vertex_count((unsigned int)data.indices.size()), vao(init(data)) {}
};


#endif //OPENGLPROJECT_MODEL_H
