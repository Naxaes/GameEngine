//
// Created by Ted Klein Bergman on 3/15/18.
//

#include "texture.h"

#include <stb_image.h>

#include "gl_debug.h"


Texture::Texture(const char *filepath)
{
    int width, height, channels;
    unsigned char *data = stbi_load(filepath, &width, &height, &channels, 0);

    if (!data)
        return;

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    id = textureID;
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::bind(unsigned int unit)
{
    GLCALL(glActiveTexture(GL_TEXTURE0 + unit));
    GLCALL(glBindTexture(GL_TEXTURE_2D, id));
}
