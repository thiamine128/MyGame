#pragma once

#include "rendering/glhelper.h"
#include "rendering/TextureAtlas.h"
#include <string>
#include <unordered_map>

class TextureManager
{
public:
    static Texture const* getTexture(std::string const&);

    static void initAtlas();
    static void terminate();

    static TextureAtlas* tiles;
protected:
    static std::unordered_map<std::string, Texture*> entries;
};