#pragma once

class Shader;
class Mesh;
class Texture;

#include "TextureUVSet.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

class Model
{
public:
    Model(const char*);
    Model(const char*, TextureUVSet const&);
    ~Model();

    void render(const Shader*) const;
    const Mesh* getMesh(int) const;
    std::vector<Mesh*> const& getMeshes() const;
protected:
    std::vector<Mesh*> meshes;
    std::string dir;
    bool texture;
    TextureUVSet uvCoord;
    
    void load(std::string const&);
    void processNode(aiNode*, const aiScene*);
    Mesh* processMesh(aiMesh*, const aiScene*);
    std::vector<Texture const*> loadMaterialTexture(aiMaterial*, aiTextureType);
};