#include "test.h"
#ifndef MAIN

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


GLint transformation_location = 0;


class DisplacementComponent : public Component
{
public:

    glm::vec3 location;
    glm::vec3 rotation;
    glm::vec3 scale;

    DisplacementComponent(const Entity& entity, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale) :
            Component(entity), location(location), rotation(rotation), scale(scale) {}

    ~DisplacementComponent() = default;
};

class GraphicComponent : public Component
{
public:

    GLuint model, texture, vertex_count;
    DisplacementComponent* displacement;

    GraphicComponent(const Entity& entity, GLuint model, GLuint texture, GLuint vertex_count) :
            Component(entity), model(model), texture(texture), vertex_count(vertex_count)
    {
        displacement = &entity.get_component<DisplacementComponent>();
    }

    ~GraphicComponent() = default;

    void update()
    {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, displacement->location);
        trans = glm::rotate(trans, glm::radians(displacement->rotation.z * 360.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        GLCALL(glUniformMatrix4fv(transformation_location, 1, GL_FALSE, glm::value_ptr(trans)));

        GLCALL(glBindVertexArray(model));
        GLCALL(glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0));
    }
};




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


void draw(GLuint program, Entity entity)
{
    GLCALL(glClearColor(0.2, 0.3, 0.8, 1.0));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    GLCALL(glUseProgram(program));

    GLCALL(transformation_location = glGetUniformLocation(program, "transformation"));

    glm::mat4 view = glm::lookAt(
            glm::vec3(1.2f, 1.2f, 1.2f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    );
    GLCALL(GLint view_location = glGetUniformLocation(program, "view"));
    GLCALL(glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view)));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLCALL(GLint projection_location = glGetUniformLocation(program, "projection"));
    GLCALL(glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection)));


    entity.update();

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


    Entity entity;

    glm::vec3 location{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};

    entity.add_component<DisplacementComponent>(location, rotation, scale);
    entity.add_component<GraphicComponent>(vao, 0, (unsigned int) data.indices.size());


    while (!glfwWindowShouldClose(window))
    {
        double start = glfwGetTime();

        draw(programID, entity);

        glfwSwapBuffers(window);
        glfwPollEvents();

        DisplacementComponent& displacement = entity.get_component<DisplacementComponent>();
        displacement.location.x = (float)std::sin(start);
        displacement.rotation.z = (float)std::cos(start);

        std::string title = "Milliseconds per frame: " + std::to_string(glfwGetTime() - start).substr(0, 5);
        glfwSetWindowTitle(window, title.c_str());
    }


    terminate(window);

    return 0;


}

#endif