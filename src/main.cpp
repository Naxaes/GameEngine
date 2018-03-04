#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Window.h"
#include "gl_debug.h"

bool initialize_opengl()
{
    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    // Must call glfwMakeContextCurrent(window) before initializing glad!
    return (bool) gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}


struct ShaderSources
{
    std::string vertex;
    std::string fragment;
};

ShaderSources load_shaders(const char* filpath)
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filpath);

    ShaderType type = static_cast<ShaderType>(ShaderType::NONE);
    std::stringstream shader_sources[2];
    std::string line;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = static_cast<ShaderType>(ShaderType::VERTEX);
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = static_cast<ShaderType>(ShaderType::FRAGMENT);
            }
            else
            {
                std::cerr << "Couldn't parse shader." << std::endl;
                exit(-1);
            }
        }
        else
        {
            shader_sources[(int)type] << line << std::endl;
        }
    }

    return {shader_sources[0].str(), shader_sources[1].str()};
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

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    GLuint vbo;
    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), positions, GL_STATIC_DRAW));

    GLuint ibo;
    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW));

    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0));
    GLCALL(glEnableVertexAttribArray(0));


    // Shaders
    ShaderSources sources = load_shaders("../res/shaders/basic.glsl");

    const char* vertex_source = sources.vertex.c_str();
    const char* fragment_source = sources.fragment.c_str();


//    std::cout << "Vertex shader" << std::endl;
//    std::cout << vertex_source << std::endl;
//    std::cout << "--------------------------\nFragment shader" << std::endl;
//    std::cout << fragment_source << std::endl;


    GLuint vertexID;
    GLCALL(vertexID = glCreateShader(GL_VERTEX_SHADER));
    GLCALL(glShaderSource(vertexID, 1, &vertex_source, nullptr));
    GLCALL(glCompileShader(vertexID));
    check_shader_status(vertexID, GL_COMPILE_STATUS);

    GLuint fragmentID;
    GLCALL(fragmentID = glCreateShader(GL_FRAGMENT_SHADER));
    GLCALL(glShaderSource(fragmentID, 1, &fragment_source, nullptr));
    GLCALL(glCompileShader(fragmentID));
    check_shader_status(fragmentID, GL_COMPILE_STATUS);

    GLuint programID;
    GLCALL(programID = glCreateProgram());

    GLCALL(glAttachShader(programID, vertexID));
    GLCALL(glAttachShader(programID, fragmentID));

    GLCALL(glBindAttribLocation(programID, 0, "position"));

    GLCALL(glLinkProgram(programID));
    check_program_status(programID, GL_LINK_STATUS);

    GLCALL(glValidateProgram(programID));
    check_program_status(programID, GL_VALIDATE_STATUS);


    GLCALL(glDeleteShader(vertexID));
    GLCALL(glDeleteShader(fragmentID));


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