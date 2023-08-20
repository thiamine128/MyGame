#include "TextureAtlas.h"

#include "TextureManager.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

TextureAtlas::TextureAtlas(const char* texturePath, const char* atlasPath)
{
    this->texture = TextureManager::getTexture(texturePath);

    std::ifstream atlasFile;
    atlasFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        atlasFile.open(atlasPath);
        std::stringstream atlasStream;
        atlasStream << atlasFile.rdbuf();
        atlasFile.close();
        atlasStream >> this->width >> this->height;
        std::string sprite;
        while (atlasStream >> sprite) {
            int x, y, w, h;
            atlasStream >> x >> y >> w >> h;
            TextureUVSet uvSet;
            uvSet.coords[0] = glm::vec2((float) (x + w) / this->width, (float) y / this->height);
            uvSet.coords[1] = glm::vec2((float) (x + w) / this->width, (float) (y + h) / this->height);
            uvSet.coords[2] = glm::vec2((float) (x) / this->width, (float) (y) / this->height);
            uvSet.coords[3] = glm::vec2((float) (x) / this->width, (float) (y + h) / this->height);
            entries[sprite] = uvSet;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

const Texture *TextureAtlas::getTexture() const
{
    return this->texture;
}

TextureUVSet const& TextureAtlas::getUVSet(std::string const& name)
{
    return this->entries[name];
}
