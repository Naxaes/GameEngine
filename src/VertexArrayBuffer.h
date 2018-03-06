//
// Created by Ted Klein Bergman on 3/5/18.
//

#ifndef OPENGLPROJECT_VERTEXARRAYBUFFER_H
#define OPENGLPROJECT_VERTEXARRAYBUFFER_H

#include <glad/glad.h>

GLuint create_vertex_buffer(GLfloat positions[], unsigned int count, unsigned int mode = GL_STATIC_DRAW);
GLuint create_index_buffer(GLuint indices[], unsigned int count, unsigned int mode = GL_STATIC_DRAW);
GLuint create_array_buffer();
void bind_to_vao(GLuint vao, GLuint vbo, GLuint ibo, unsigned char count_per_vertex);

#endif //OPENGLPROJECT_VERTEXARRAYBUFFER_H
