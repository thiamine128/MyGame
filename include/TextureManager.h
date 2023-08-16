#pragma once

#include "rendering/Texture.h"

#include <string>
#include <unordered_map>

class TextureManager
{
public:
    ~TextureManager();

    Texture const* getTexture(std::string const&);

    static TextureManager* getInstance();
    static void terminate();
protected:
    std::unordered_map<std::string, Texture*> entries;

    TextureManager();

    static TextureManager* instance;
};