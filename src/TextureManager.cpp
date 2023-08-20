#include "TextureManager.h"

#include <stb_image.h>

std::unordered_map<std::string, Texture*> TextureManager::entries;
TextureAtlas* TextureManager::tiles;

Texture const* TextureManager::getTexture(std::string const& path)
{
    if (entries.count(path) == 0)
    {
        entries[path] = new Texture(path.c_str());
    }
    return entries[path];
}

void TextureManager::initAtlas()
{
    tiles = new TextureAtlas("assets/texture/tiles.png", "assets/texture/tiles.atlas");
}

void TextureManager::terminate()
{
    for (auto e : entries) {
        delete e.second;
    }
    delete tiles;
}
