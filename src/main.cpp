#include "../tests/EntityTest.h"
#include "../tests/MatrixTest.h"
#include "../tests/TemporaryTest.h"


#if !RUN_ENTITY_TEST && !RUN_MATRIX_TEST && !RUN_TEMPORARYTEST



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


class DisplacementComponent : public Component
{
public:

    glm::vec3 location;
    glm::vec3 rotation;
    glm::vec3 scale;

    DisplacementComponent(const Entity& entity, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale) :
            Component(entity), location(location), rotation(rotation), scale(scale) {}
    ~DisplacementComponent() = default;

    void update(
            float x  = 0.0f, float y  = 0.0f, float z  = 0.0f,
            float rx = 0.0f, float ry = 0.0f, float rz = 0.0f,
            float sx = 0.0f, float sy = 0.0f, float sz = 0.0f
    )
    {
        if (!x)
            return;

        location.x += x;
        location.y += y;
        location.z += z;

        rotation.x += rx;
        rotation.y += ry;
        rotation.z += rz;

        scale.x += sx;
        scale.y += sy;
        scale.z += sz;
    };
};

class GraphicComponent : public Component
{
public:

    VertexArray vao;
    GLuint texture, vertex_count;
    DisplacementComponent* displacement;

    GraphicComponent(const Entity& entity, VertexArray vao, GLuint texture, GLuint vertex_count) :
            Component(entity), vao(vao), texture(texture), vertex_count(vertex_count)
    {
        displacement = &entity.get_component<DisplacementComponent>();
    }

    ~GraphicComponent() = default;

    void update(Shader program)
    {
        glm::mat4 identity = glm::mat4(1.0f);
        glm::mat4 translated = glm::translate(identity, displacement->location);
        glm::mat4 rotated = glm::rotate(identity, glm::radians(displacement->rotation.z * 360.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 scaled  = glm::scale(displacement->scale);

        glm::mat4 transformation_matrix = translated * rotated * scaled;

        program.bind_uniform("transformation", transformation_matrix);

        vao.bind();
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



    OBJData data = load_obj_file("../res/models/dragon.obj");

//    GLuint vao = create_array_buffer();
//    GLuint vbo = create_vertex_buffer(&data.positions[0], (unsigned int) data.positions.size());
//    GLuint ibo = create_index_buffer(&data.indices[0], (unsigned int) data.indices.size());
//    bind_to_vao(vao, vbo, ibo, 3);


    VertexArray  vao2;
    VertexBuffer<GLfloat> vbo2(&data.positions[0], (unsigned int) data.positions.size());
    IndexBuffer  ibo2(&data.indices[0], (unsigned int) data.indices.size());

    VertexBufferLayout layout;
    layout.push<GLfloat>(3);

    vao2.add_buffer<GLfloat>(vbo2, ibo2, layout);



    std::vector<std::string> attributes;
    std::vector<std::string> uniforms;
    attributes.push_back("position");
    uniforms.push_back("transformation");
    uniforms.push_back("view");
    uniforms.push_back("projection");
    uniforms.push_back("time");
    Shader program("../res/shaders/basic.glsl", attributes, uniforms);

    ComponentManager manager;
    Entity entity = manager.create_entity();

    glm::vec3 location{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{0.1f, 0.1f, 0.1f};

    entity.add_component<DisplacementComponent>(location, rotation, scale);
    entity.add_component<GraphicComponent>(vao2, 0, (unsigned int) data.indices.size());


    GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glEnable(GL_CULL_FACE));   // Cannot do single call with bitwise operation. Don't know why.

    GLCALL(glClearColor(0.2, 0.3, 0.8, 1.0));
    GLCALL(glCullFace(GL_BACK));

    glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f,  -2.0f),
            glm::vec3(0.0f, 0.0f,   0.0f),
            glm::vec3(0.0f, 1.0f,   0.0f)
    );
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);

    program.bind();  // TODO(ted): Must bind before binding uniform. Make it throw better error messages if it's not.
    program.bind_uniform("view", view);
    program.bind_uniform("projection", projection);

    while (!glfwWindowShouldClose(window))
    {
        double start = glfwGetTime();

        GLCALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));

        program.bind();
        program.bind_uniform("time", (float)start);

        manager.update<DisplacementComponent>();
        manager.update<GraphicComponent>(program);

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