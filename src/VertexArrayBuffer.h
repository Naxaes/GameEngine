//
// Created by Ted Klein Bergman on 3/5/18.
//

#ifndef OPENGLPROJECT_VERTEXARRAYBUFFER_H
#define OPENGLPROJECT_VERTEXARRAYBUFFER_H

#include <glad/glad.h>

GLuint create_vertex_buffer(GLfloat positions[]);
GLuint create_index_buffer(GLuint indices[]);
GLuint create_array_buffer();
GLuint bind_to_vao(GLuint vao, GLuint vbo, GLuint ibo);

#endif //OPENGLPROJECT_VERTEXARRAYBUFFER_H
