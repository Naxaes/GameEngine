//
// Created by Ted Klein Bergman on 3/4/18.
//

#ifndef OPENGLPROJECT_WINDOW_H
#define OPENGLPROJECT_WINDOW_H

struct GLFWwindow;

GLFWwindow* create_window(unsigned short width, unsigned short height, const char* title);
void mainloop(GLFWwindow* window, void (*function)());
void terminate(GLFWwindow* window);
void initialize();



class Window
{
public:
    Window(unsigned short width, unsigned short height, const char* title);
    ~Window();
private:
    GLFWwindow* handle;
};




#endif // OPENGLPROJECT_WINDOW_H
