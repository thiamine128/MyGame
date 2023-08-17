#pragma once

#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

class Model
{
public:
    Model(const char*);
    ~Model();

    void render(const Shader*) const;
protected:
    std::vector<Mesh*> meshes;
    std::string dir;

    void load(std::string const&);
    void processNode(aiNode*, const aiScene*);
    Mesh* processMesh(aiMesh*, const aiScene*);
    std::vector<Texture const*> loadMaterialTexture(aiMaterial*, aiTextureType);
};