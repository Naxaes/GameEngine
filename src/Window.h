//
// Created by Ted Klein Brgman on 3/4/18.
//

#ifndef OPENGLPROJECT_WINDOW_H
#define OPENGLPROJECT_WINDOW_H

struct GLFWwindow;

GLFWwindow* create_window(unsigned short width, unsigned short height, const char* title);
void mainloop(GLFWwindow* window, void (*function)());
void terminate(GLFWwindow* window);

bool initialize_glfw();

#endif // OPENGLPROJECT_WINDOW_H
