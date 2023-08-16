#pragma once

#include "rendering/Vertex.h"
#include "rendering/Texture.h"
#include "rendering/Shader.h"
#include "rendering/VertexArrayObject.h"
#include "rendering/VertexBufferObject.h"
#include "rendering/ElementBufferObject.h"

#include <vector>

class Mesh
{
public:
    Mesh(std::vector<Vertex>&, std::vector<unsigned int>&, std::vector<Texture const*>&);
    ~Mesh();

    void render(Shader*) const;
protected:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture const*> textures;
    
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    ElementBufferObject* ebo;

    void setup();
};