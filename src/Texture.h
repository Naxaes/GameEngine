//
// Created by Ted Klein Bergman on 3/15/18.
//

#ifndef OPENGLPROJECT_TEXTURE_H
#define OPENGLPROJECT_TEXTURE_H

#include <glad/glad.h>


class Texture
{
private:


public:
    GLuint id;

    explicit Texture(const char* filepath);
    ~Texture();

    void bind(unsigned int unit = 0);
};


#endif //OPENGLPROJECT_TEXTURE_H
