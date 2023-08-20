#include "Texture.h"

#include <stb_image.h>

#include <iostream>

Texture::Texture()
{
    glGenTextures(1, &(this->id));
}

Texture::Texture(const char *path)
{
    glGenTextures(1, &(this->id));
    this->loadImage(path);
}

Texture::~Texture()
{
    glDeleteTextures(1, &(this->id));
}

void Texture::loadImage(const char* path)
{
    unsigned char* data = stbi_load(path, &(this->width), &(this->height), &(this->nrChannels), STBI_rgb);

    if (data) {
        
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

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

int Texture::getWidth() const
{
    return this->width;
}

void Texture::attachToFramebuffer(GLenum attachment) const
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, this->id, 0);
}

void Texture::setupDepthMap(int width, int height) const
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
