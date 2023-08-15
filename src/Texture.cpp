#include "Texture.h"

#include <stb_image.h>

#include <iostream>

Texture::Texture(const char* path)
{
    unsigned char* data = stbi_load(path, &(this->width), &(this->height), &(this->nrChannels), STBI_rgb);

    if (data) {
        glGenTextures(1, &(this->id));
        this->bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load image : " << path << "." << std::endl;
    }

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &(this->id));
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}
