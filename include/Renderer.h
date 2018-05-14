//
// Created by Ted Klein Bergman on 3/28/18.
//

#ifndef OPENGLPROJECT_RENDERER_H
#define OPENGLPROJECT_RENDERER_H

#include <glad/glad.h>

#include "gl_debug.h"


class Renderer
{
private:



public:
    Renderer()
    {
        GLCALL(glEnable(GL_DEPTH_TEST));
        GLCALL(glEnable(GL_CULL_FACE));   // Cannot do single call with bitwise operation. Don't know why.

        GLCALL(glClearColor(0.05, 0.05, 0.10, 1.0));
        GLCALL(glCullFace(GL_BACK));
    }

    void clear()
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
    }

};


#endif //OPENGLPROJECT_RENDERER_H
