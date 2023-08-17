#pragma once

#include "rendering/Texture.h"

#include <string>
#include <unordered_map>

class TextureManager
{
public:
    static Texture const* getTexture(std::string const&);

    static void terminate();
protected:
    static std::unordered_map<std::string, Texture*> entries;
};