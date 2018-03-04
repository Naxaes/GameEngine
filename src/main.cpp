#include <iostream>

#include <glad/glad.h>       // Must include glad before glfw!
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "gl_debug.h"

void framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void window_close_callback(GLFWwindow* window)
{
    std::cout << "Closing the application." << std::endl;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
    std::cout << "Character: " << codepoint << std::endl;
}

void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods)
{
    std::cout << "Character: " << codepoint << " with mods " << mods << std::endl;
}

static void cursor_position_callback(GLFWwindow* window, double x, double y)
{
    // std::cout << "Mouse position: " << x << ", " << y << std::endl;
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (entered)
        std::cout << "Welcome back mouse!" << std::endl;
    else
        std::cout << "Come back here, mouse!" << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        std::cout << "Clicked!" << std::endl;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "Scrolling: " << xoffset << ", " << yoffset << std::endl;
}

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    for (int i = 0;  i < count;  i++)
        std::cout << "Dropped file: " << paths[i] << std::endl;
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

    // CALLBACKS - If you don't need to be notified via callbacks, all these can be queried through function calls.

    // Window events
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    glfwSetWindowCloseCallback(window, window_close_callback);

    // Keyboard events
    glfwSetKeyCallback(window, key_callback);
    glfwSetCharCallback(window, character_callback);
    glfwSetCharModsCallback(window, charmods_callback);

    // Mouse events
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Path drop
    glfwSetDropCallback(window, drop_callback);

    if (window == nullptr)
        throw std::runtime_error("Failed to create GLFW window.");

    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        std::runtime_error("Failed to initialize OpenGL context");


    std::cout << "[Initialization] GLFW   Version: " << glfwGetVersionString()  << std::endl;
    std::cout << "[Initialization] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;


}