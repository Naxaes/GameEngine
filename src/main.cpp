#include <iostream>

#include <glad/glad.h>       // Must include glad before glfw!
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "gl_debug.h"

void framebuffer_resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // Initialize window and OpenGL

    // http://www.glfw.org/docs/latest/window_guide.html
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(420, 420, "OpenGL Project", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize);


    if (window == nullptr)
        throw std::runtime_error("Failed to create GLFW window.");

    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        std::runtime_error("Failed to initialize OpenGL context");


    std::cout << "[Initialization] GLFW   Version: " << glfwGetVersionString()  << std::endl;
    std::cout << "[Initialization] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;






    std::cout << "Hello world!" << std::endl;

    return 0;


}