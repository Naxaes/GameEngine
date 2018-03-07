#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Window.h"
#include "gl_debug.h"
#include "debug.h"
#include "Shader.h"
#include "VertexArrayBuffer.h"
#include "Loader.h"
#include "Entity.h"

bool initialize_opengl()
{
    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    // Must call glfwMakeContextCurrent(window) before initializing glad!

    // https://github.com/Dav1dde/glad

    // glad_set_pre_callback(_pre_gl_call_callback);
    // glad_set_post_callback(_post_gl_call_callback);

    // Removed post and pre callback functionality since GLCALL(x) gives better errors.
    return (bool) gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}


void draw(GLuint program, World world)
{
    GLCALL(glClearColor(0.2, 0.3, 0.8, 1.0));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    GLCALL(glUseProgram(program));

    GLCALL(GLint transformation_location = glGetUniformLocation(program, "transformation"));

    for (unsigned int entityID = 0; entityID < world.entity_count; entityID++)
    {
        Graphics graphics = world.entity_graphics[entityID];
        Displacement* displacement = graphics.displacement;

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(displacement->x, displacement->y, displacement->z));
        trans = glm::rotate(trans, glm::radians(displacement->rz * 360.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        GLCALL(glUniformMatrix4fv(transformation_location, 1, GL_FALSE, glm::value_ptr(trans)));

        GLCALL(glBindVertexArray(graphics.model));
        GLCALL(glDrawElements(GL_TRIANGLES, graphics.vertex_count, GL_UNSIGNED_INT, 0));
    }

}


int main()
{
    // Must first initialize GLFW to create.
    // Then create window (OpenGL context)
    // Then initialize glad.


    ASSERT(initialize_glfw(), "Failed to initialize GLFW.");
    std::cout << "[Initialization] GLFW Version: " << glfwGetVersionString()  << std::endl;

    GLFWwindow* window = create_window(420, 420, "OpenGL Project");
    ASSERT(window, "Failed to create GLFW window.");

    ASSERT(initialize_opengl(), "Failed to initialize OpenGL context.");
    std::cout << "[Initialization] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;



    OBJData data = load_obj_file("../res/models/cube.obj");

    GLuint vao = create_array_buffer();
    GLuint vbo = create_vertex_buffer(&data.positions[0], (unsigned int) data.positions.size());
    GLuint ibo = create_index_buffer(&data.indices[0], (unsigned int) data.indices.size());
    bind_to_vao(vao, vbo, ibo, 3);

    GLuint programID = create_shader_program("../res/shaders/basic.glsl");


    World world(100);

    Displacement displacement = {0, 0, 0, 0, 0, 0, 1, 1, 1};
    Movement movement = {0};
    Graphics graphics = {&displacement, vao, (unsigned int) data.indices.size(), 0};

    world.entity_create(displacement, movement, graphics);

    while (!glfwWindowShouldClose(window))
    {
        double start = glfwGetTime();

        draw(programID, world);

        glfwSwapBuffers(window);
        glfwPollEvents();

        displacement.x = (float)std::sin(start);
        displacement.rz = (float)std::cos(start);

        std::string title = "Milliseconds per frame: " + std::to_string(glfwGetTime() - start).substr(0, 5);
        glfwSetWindowTitle(window, title.c_str());
    }


    terminate(window);

    return 0;


}