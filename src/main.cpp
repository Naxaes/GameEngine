#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "gl_debug.h"
#include "debug.h"
#include "Shader.h"
#include "VertexArrayBuffer.h"
#include "Loader.h"

bool initialize_opengl()
{
    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    // Must call glfwMakeContextCurrent(window) before initializing glad!
    return (bool) gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}


void draw(GLuint program, GLuint vao, unsigned int count)
{
    GLCALL(glClearColor(0.2, 0.3, 0.8, 1.0));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    GLCALL(glUseProgram(program));
    GLCALL(glBindVertexArray(vao));
    GLCALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0));
}


int main()
{
    ASSERT(initialize_glfw(), "Failed to initialize GLFW.");
    std::cout << "[Initialization] GLFW Version: " << glfwGetVersionString()  << std::endl;

    GLFWwindow* window = create_window(420, 420, "OpenGL Project");

    ASSERT(window, "Failed to create GLFW window.");

    ASSERT(initialize_opengl(), "Failed to initialize OpenGL context.");
    std::cout << "[Initialization] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


    // VBO and IBO.
    GLfloat positions[] = {
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f
    };

    GLuint indices[] = {
         0, 1, 3,
         3, 1, 2
    };

    OBJData data = load_obj_file("../res/models/cube.obj");

    GLuint vao = create_array_buffer();
    GLuint vbo = create_vertex_buffer(&data.positions[0], (unsigned int) data.positions.size());
    GLuint ibo = create_index_buffer(&data.indices[0], (unsigned int) data.indices.size());
    bind_to_vao(vao, vbo, ibo, 3);

    GLuint programID = create_shader_program("../res/shaders/basic.glsl");

    while (!glfwWindowShouldClose(window))
    {
        double start = glfwGetTime();

        draw(programID, vao, (unsigned int) data.indices.size());

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::string title = "Milliseconds per frame: " + std::to_string(glfwGetTime() - start).substr(0, 5);
        glfwSetWindowTitle(window, title.c_str());
    }


    terminate(window);

    return 0;


}