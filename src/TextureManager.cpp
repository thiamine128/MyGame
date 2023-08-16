#include "TextureManager.h"

#include <stb_image.h>

TextureManager* TextureManager::instance = nullptr;

TextureManager::~TextureManager()
{
}

Texture const* TextureManager::getTexture(std::string const& path)
{
    if (this->entries.count(path) == 0)
    {
        this->entries[path] = new Texture(path.c_str());
    }
    return this->entries[path];
}

TextureManager *TextureManager::getInstance()
{
    if (instance == nullptr) {
        instance = new TextureManager();
    }
    return instance;
}

void TextureManager::terminate()
{
    delete instance;
}

TextureManager::TextureManager()
{
    //stbi_set_flip_vertically_on_load(true);
}
