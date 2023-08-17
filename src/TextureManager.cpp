#include "TextureManager.h"

#include <stb_image.h>

std::unordered_map<std::string, Texture*> TextureManager::entries;

Texture const* TextureManager::getTexture(std::string const& path)
{
    if (entries.count(path) == 0)
    {
        entries[path] = new Texture(path.c_str());
    }
    return entries[path];
}

void TextureManager::terminate()
{
    for (auto e : entries) {
        delete e.second;
    }
}
