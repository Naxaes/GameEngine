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


#include "Window.h"
#include "gl_debug.h"
#include "debug.h"
#include "Shader.h"
#include "VertexArrayBuffer.h"
#include "Loader.h"
#include "Entity.h"
#include "Texture.h"
#include "Model.h"

#include "Displacement.h"
#include "Graphics.h"


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

int main()
{
    // Must first initialize GLFW to create.
    // Then create window (OpenGL context)
    // Then initialize glad.

    GLFWwindow* window = create_window(420, 420, "OpenGL Project");
    ASSERT(window, "Failed to create GLFW window.");

    ASSERT(initialize_opengl(), "Failed to initialize OpenGL context.");
    std::cout << "[Initialization] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    
    // MODEL START
    OBJData data = load_obj_file("../res/models/cube.obj", false);
    Model model1{data};
    // MODEL END


    // SHADER START
    Shader* program = create_shader();
    // SHADER END



    // ENTITY START
    Entity entity{};

    glm::vec3 location{0, 0, 1.0f};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};

    entity.add_component<DisplacementComponent>(location, rotation, scale);
    entity.add_component<GraphicComponent>(model1.vao, 0, model1.vertex_count, *program);
    // ENTITY END

    // LIGHT START
//    Entity light = manager.create_entity();
//
//    glm::vec3 light_location{0, 0, 1.0f};
//    glm::vec3 light_rotation{0, 0, 0};
//    glm::vec3 light_scale{1.0f, 1.0f, 1.0f};
//
//    // TODO(ted): This overwrites the entities components.
//    light.add_component<DisplacementComponent>(light_location, light_rotation, light_scale);
//    light.add_component<GraphicComponent>(model1.vao, 0, model1.vertex_count);
    // LIGHT END

    Texture texture_diffuse("../res/textures/Container.png");
    Texture texture_specular("../res/textures/ContainerSpecular.png");
    Texture texture_emission("../res/textures/ContainerEmission.png");
    ASSERT(texture_diffuse.id != 0, "Coulnd't load texture.");
    ASSERT(texture_specular.id != 0, "Coulnd't load texture.");
    ASSERT(texture_emission.id != 0, "Coulnd't load texture.");

    GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glEnable(GL_CULL_FACE));   // Cannot do single call with bitwise operation. Don't know why.

    GLCALL(glClearColor(0.05, 0.05, 0.10, 1.0));
    GLCALL(glCullFace(GL_BACK));

    glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f,  -4.0f),
            glm::vec3(0.0f, 0.0f,   0.0f),
            glm::vec3(0.0f, 1.0f,   0.0f)
    );
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);

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

    double start = glfwGetTime();
    double stop  = start;

    while (!glfwWindowShouldClose(window))
    {
        double dt = stop - start;
        start = glfwGetTime();

        GLCALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));

        program->bind();
        program->bind_texture(texture_diffuse.id,  0);
        program->bind_texture(texture_specular.id, 1);
        program->bind_texture(texture_emission.id, 2);

        program->bind_uniform("time", (float)start);
//        program->bind_uniform("light_position", 0, 0, ((float)std::cos(start) + 1.0f) * 2);

        entity.update((float)dt);

        glfwSwapBuffers(window);
        glfwPollEvents();

        DisplacementComponent& displacement = entity.get_component<DisplacementComponent>();
        displacement.rotation.y = (float)std::cos(start / 10) * 360;
        displacement.location.y = (float)std::sin(start / 10);
        displacement.rotation.x = (float)std::cos(start) * 45;
        displacement.location.x = (float)std::sin(start);

//        DisplacementComponent& light_displacement = light.get_component<DisplacementComponent>();
//        light_displacement.location.x = (float)std::sin(start) * 2;
//        light_displacement.location.z = (float)std::cos(start) * 2;

        std::string title = "Milliseconds per frame: " + std::to_string(dt).substr(0, 5);
        glfwSetWindowTitle(window, title.c_str());

        stop = glfwGetTime();
    }

    terminate(window);

    return 0;


}