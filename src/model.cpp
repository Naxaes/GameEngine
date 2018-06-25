//
// Created by Ted Klein Bergman on 3/29/18.
//

#include "model.h"

//
//VertexArray Model::init(OBJData data)
//{
//    VertexArray vao;
//
//    VertexBuffer* vbo_data = VertexBuffer::create<GLfloat>(data.data);
//    IndexBuffer*  ibo = IndexBuffer::create<GLuint>(data.indices);
//
//    VertexBufferLayout layout;
//    layout.push<GLfloat>(*vbo_data, 3);
//    layout.push<GLfloat>(*vbo_data, 2);
//    layout.push<GLfloat>(*vbo_data, 3);
//
//    vao.add_buffer(*ibo, layout);
//
//    return vao;
//}