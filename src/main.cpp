#include <iostream>

#include "Window.h"
#include "gl_debug.h"

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
        std::cout << "[Initialization] GLFW   Version: " << glfwGetVersionString()  << std::endl;
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

    mainloop(window);
    terminate(window);

    return 0;


}