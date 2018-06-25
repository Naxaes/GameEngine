#define GLFW_INCLUDE_NONE

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "window.h"
#include "renderer.h"
#include "shader.h"
#include "vertex_array_buffer.h"
//#include "obj_loader.h"
#include "entity.h"
#include "texture.h"
#include "model.h"



Shader* create_shader()
{
    std::vector<std::string> attributes;
    std::vector<std::string> uniforms;

    attributes.push_back("position");
    attributes.push_back("texture_coordinates");
    attributes.push_back("normals");

    uniforms.push_back("transformation");
    uniforms.push_back("view");
    uniforms.push_back("projection");

    uniforms.push_back("camera_position");

    uniforms.push_back("diffuse");
    uniforms.push_back("specular");
    uniforms.push_back("emission");

    uniforms.push_back("time");
    uniforms.push_back("ambient");
    uniforms.push_back("shininess");

    uniforms.push_back("light_position");
    uniforms.push_back("light_linear");
    uniforms.push_back("light_quadratic");

    return new Shader("../res/shaders/basic.glsl", attributes, uniforms);
}

void bind_program(const Shader* program, const glm::mat4& view, const glm::mat4& projection)
{
    program->bind();

    program->bind_uniform("view", view);
    program->bind_uniform("projection", projection);

    program->bind_uniform("camera_position", 0.0f, 0.0f, -4.0f);

    program->bind_uniform("ambient", 0.2f);
    program->bind_uniform("diffuse",  0);
    program->bind_uniform("specular", 1);
    program->bind_uniform("emission", 2);

    program->bind_uniform("time", 0.0f);
    program->bind_uniform("shininess", 64.0f);

    program->bind_uniform("light_position", 0.0f, 0.0f, -2.0f);
    program->bind_uniform("light_linear", 0.09f);
    program->bind_uniform("light_quadratic", 0.032f);
}

void bind_textures(const Shader* program, const Texture& texture_diffuse, const Texture& texture_specular,
                   const Texture& texture_emission)
{
    program->bind_texture(texture_diffuse.id, 0);
    program->bind_texture(texture_specular.id, 1);
    program->bind_texture(texture_emission.id, 2);
}

int main()
{
    // Must first initialize GLFW to create.
    // Then create window (OpenGL context)
    // Then initialize glad.

//    GLFWwindow* window = create_window(420, 420, "OpenGL Project");
    Window window(420, 420, "OpenGL Project");
    std::cout << "[Initialization] " << window.version() << std::endl;

    Renderer renderer;
    std::cout << "[Initialization] " << renderer.version() << std::endl;


    // MODEL START

    // MODEL END


    // SHADER START
    Shader* program = create_shader();
    // SHADER END


    Texture texture_diffuse("../res/textures/Container.png");
    Texture texture_specular("../res/textures/ContainerSpecular.png");
    Texture texture_emission("../res/textures/ContainerEmission.png");
    ASSERT(texture_diffuse.id != 0, "Coulnd't load texture.");
    ASSERT(texture_specular.id != 0, "Coulnd't load texture.");
    ASSERT(texture_emission.id != 0, "Coulnd't load texture.");


    glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f,  -4.0f),
            glm::vec3(0.0f, 0.0f,   0.0f),
            glm::vec3(0.0f, 1.0f,   0.0f)
    );
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);

    bind_program(program, view, projection);

    double start = glfwGetTime();
    double stop  = start;

    while (!window.exit_requested())
    {
        double dt = stop - start;
        start = glfwGetTime();

        program->bind();
        program->bind_uniform("time", (float)start);
        bind_textures(program, texture_diffuse, texture_specular, texture_emission);

        window.clear();

        // Draw

        window.update();
        window.set_title("Milliseconds per frame: " + std::to_string(dt).substr(0, 5));

        stop = glfwGetTime();
    }

    return 0;


}