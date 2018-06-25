//
// Created by Ted Klein Bergman on 3/4/18.
//

#ifndef OPENGLPROJECT_WINDOW_H
#define OPENGLPROJECT_WINDOW_H

#include <glad/glad.h>       // Must include glad before glfw!
#include <GLFW/glfw3.h>
#include <string>

GLFWwindow* create_window(unsigned short width, unsigned short height, const char* title);
void mainloop(GLFWwindow* window, void (*function)());
void terminate(GLFWwindow* window);
void initialize();



class Window
{
public:
    Window(unsigned short width, unsigned short height, const char* title);
    ~Window();
    bool exit_requested();
    void set_title(const std::string& title);
    std::string version();
    void update();
    void clear();
private:
    GLFWwindow* handle;
};

//
//struct ContextOptions
//{
//    uint8_t version_major = 3;
//    uint8_t version_minor = 3;
//    //  one where all functionality deprecated in the requested version of OpenGL is removed. This must only be used
//    // if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored.
//    bool forward_compatible = true;
//    bool debug = true;
//
//
//    CONTEXT_VERSION_MAJOR = 0; // 3);
//    CONTEXT_VERSION_MINOR = 0; // 3);
//    OPENGL_FORWARD_COMPAT = 0; // GLFW_TRUE);
//    OPENGL_DEBUG_CONTEXT = 0;  // GLFW_TRUE);
//    OPENGL_PROFILE = 0;   // GLFW_OPENGL_CORE_PROFILE);
//    CONTEXT_NO_ERROR = 0; // GLFW_FALSE);
//    CLIENT_API = 0; // GLFW_OPENGL_API);
//};



//
//struct Event
//{
//    int type;
//    int code;
//};
//
//
//void set_window_events(GLFWwindow* window)
//{
//    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
//    glfwSetWindowCloseCallback(window, window_close_callback);
//    glfwSetWindowPosCallback(window, window_position_callback);
//}
//
//void set_keyboard_events(GLFWwindow* window)
//{
//    glfwSetKeyCallback(window, key_callback);
//    glfwSetCharCallback(window, character_callback);
//    glfwSetCharModsCallback(window, charmods_callback);
//}
//
//void set_mouse_events(GLFWwindow* window)
//{
//    glfwSetCursorPosCallback(window, cursor_position_callback);
//    glfwSetCursorEnterCallback(window, cursor_enter_callback);
//    glfwSetMouseButtonCallback(window, mouse_button_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//}
//
//void set_vsync()
//{
//    glfwSwapInterval(1);
//}
//
//void set_filedrop(GLFWwindow* window)
//{
//    glfwSetDropCallback(window, drop_callback);
//}
//
//void set_monitor_events()
//{
//    glfwSetMonitorCallback(monitor_callback);
//}
//
//void set_window_icon(GLFWwindow *window)
//{
//    glfwSetWindowIcon(window, 2, images);
//}
//
//void set_error_event()
//{
//    glfwSetErrorCallback(error_callback);
//}

#endif // OPENGLPROJECT_WINDOW_H
