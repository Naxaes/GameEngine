#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "gl_debug.h"
#include "Shader.h"
#include "VertexArrayBuffer.h"

bool initialize_opengl()
{
    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    // Must call glfwMakeContextCurrent(window) before initializing glad!
    return (bool) gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}


int main()
{

    if (!initialize_glfw())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return -1;
    }
    else
    {
        std::cout << "[Initialization] GLFW Version: " << glfwGetVersionString()  << std::endl;
    }

    GLFWwindow* window = create_window(420, 420, "OpenGL Project");

    if (!initialize_opengl())
    {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "[Initialization] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    }



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

    GLuint vao = create_array_buffer();
    GLuint vbo = create_vertex_buffer(positions);
    GLuint ibo = create_index_buffer(indices);
    bind_to_vao(vao, vbo, ibo);


    // SHADERS
    GLuint programID = create_shader_program("../res/shaders/basic.glsl");
    // END SHADERS

    while (!glfwWindowShouldClose(window))
    {
        double start = glfwGetTime();

        GLCALL(glClearColor(0.2, 0.3, 0.8, 1.0));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        GLCALL(glUseProgram(programID));
        GLCALL(glBindVertexArray(vao));
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::string title = "Milliseconds per frame: " + std::to_string(glfwGetTime() - start).substr(0, 5);
        glfwSetWindowTitle(window, title.c_str());
    }


    terminate(window);

    return 0;


}