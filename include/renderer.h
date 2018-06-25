//
// Created by Ted Klein Bergman on 3/28/18.
//

#ifndef OPENGLPROJECT_RENDERER_H
#define OPENGLPROJECT_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "gl_debug.h"
#include "debug.h"


class Renderer
{
private:



public:
    Renderer()
    {
        // Load all OpenGL functions using the glfw loader function
        // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
        // Must call glfwMakeContextCurrent(window) before initializing glad!

        // https://github.com/Dav1dde/glad

        // glad_set_pre_callback(_pre_gl_call_callback);
        // glad_set_post_callback(_post_gl_call_callback);

        // Removed post and pre callback functionality since GLCALL(x) gives better errors.
        ASSERT(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to initialize OpenGL context.");

        GLCALL(glEnable(GL_DEPTH_TEST));
        GLCALL(glEnable(GL_CULL_FACE));   // Cannot do single call with bitwise operation. Don't know why.

        GLCALL(glClearColor(0.05, 0.05, 0.10, 1.0));
        GLCALL(glCullFace(GL_BACK));
    }

    void clear()
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
    }

    std::string version()
    {
        return "OpenGL version " + std::to_string(*glGetString(GL_VERSION));
    }

};


#endif //OPENGLPROJECT_RENDERER_H
