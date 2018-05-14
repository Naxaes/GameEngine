//
// Created by Ted Klein Bergman on 3/4/18.
//
#include "Window.h"
#include "debug.h"

#include <iostream>
#include <array>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>       // Must include glad before glfw!
#include <GLFW/glfw3.h>



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

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void monitor_callback(GLFWmonitor* monitor, int event)
{
    if (event == GLFW_CONNECTED)
        std::cout << "The monitor was connected" << std::endl;
    else if (event == GLFW_DISCONNECTED)
        std::cout << "The monitor was disconnected" << std::endl;
}

void window_position_callback(GLFWwindow* window, int x, int y)
{
    std::cout << "Stop moving the window!" << std::endl;
}

void add_context_hints()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,  GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,   GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
}

void add_window_hints()
{
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE,   GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);  // Has borders, close button, etc.
    glfwWindowHint(GLFW_FOCUSED,   GLFW_TRUE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING,  GLFW_FALSE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
}

void add_monitor_hints()
{
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);  // Highest possible.

}

void add_framebuffer_hints()
{
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
}

void add_hints()
{
    add_context_hints();
    add_framebuffer_hints();
    add_window_hints();
    add_monitor_hints();
}

void set_window_events(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetWindowPosCallback(window, window_position_callback);
}

void set_keyboard_events(GLFWwindow* window)
{
    glfwSetKeyCallback(window, key_callback);
    glfwSetCharCallback(window, character_callback);
    glfwSetCharModsCallback(window, charmods_callback);
}

void set_mouse_events(GLFWwindow* window)
{
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void set_vsync()
{
    glfwSwapInterval(1);
}

void set_filedrop(GLFWwindow* window)
{
    glfwSetDropCallback(window, drop_callback);
}

void set_monitor_events()
{
    glfwSetMonitorCallback(monitor_callback);
}

void set_window_icon(GLFWwindow *window)
{
    GLFWimage images[2];

    std::array<const char*, 2> paths {"../res/textures/icon_large.png", "../res/textures/icon_small.png"};

    for (unsigned int i = 0; i < paths.size(); i++)
    {
        int icon_width, icon_height, channels;
        unsigned char* data = stbi_load(paths[i], &icon_width, &icon_height, &channels, 0);
        images[i].width  = icon_width;
        images[i].height = icon_height;
        images[i].pixels = data;
    }

    glfwSetWindowIcon(window, 2, images);
}

void set_error_event()
{
    glfwSetErrorCallback(error_callback);
}

void set_options(GLFWwindow *window)
{
    // CALLBACKS - If you don't need to be notified via callbacks, all these can be queried through function calls.
    set_window_events(window);
    set_keyboard_events(window);
    set_mouse_events(window);
    set_monitor_events();
    set_error_event();
    set_filedrop(window);
    set_vsync();
    set_window_icon(window);
}


void terminate(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}


void initialize()
{
    ASSERT(glfwInit(), "Failed to initialize GLFW.");
    std::cout << "[Initialization] GLFW Version: " << glfwGetVersionString()  << std::endl;
}

GLFWwindow* create_window(unsigned short width, unsigned short height, const char* title)
{
    // http://www.glfw.org/docs/latest/window_guide.html

    // HINTS: http://www.glfw.org/docs/latest/window_guide.html#window_hints

    initialize();
    add_hints();

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
        return nullptr;

    glfwSetWindowSizeLimits(window, 100, 100, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowAspectRatio(window, 16, 9);

    glfwMakeContextCurrent(window);

    set_options(window);

    return window;
}

void mainloop(GLFWwindow* window, void (*function)())
{
    while (!glfwWindowShouldClose(window))
    {
        double start = glfwGetTime();

        function();

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::string title = "Milliseconds per frame: " + std::to_string(glfwGetTime() - start);
        glfwSetWindowTitle(window, title.c_str());
    }
}






Window::Window(unsigned short width, unsigned short height, const char* title)
{
    handle = create_window(width, height, title);
}

Window::~Window()
{
    terminate(handle);
}