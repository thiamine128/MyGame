#include "TextureManager.h"

#include <stb_image.h>

std::unordered_map<std::string, Texture*> TextureManager::entries;

//获取指定路径的贴图（如果没有加载则从文件系统中加载，否则返回已经加载好的贴图）
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
}

//释放内存
void TextureManager::terminate()
{
    for (auto e : entries) {
        delete e.second;
    }
}
