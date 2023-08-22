#pragma once

#include "glhelper.h"
#include "TextureUVSet.h"

#include <unordered_map>
#include <string>

class TextureAtlas
{
public:
    TextureAtlas(const char*, const char*);

    const Texture* getTexture() const;
    TextureUVSet const& getUVSet(std::string const&);
protected:
    int width, height;
    std::unordered_map<std::string, TextureUVSet> entries;
    const Texture* texture;
};