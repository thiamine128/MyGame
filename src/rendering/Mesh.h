#pragma once

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "ElementBufferObject.h"

#include <vector>

class Mesh
{
public:
    Mesh(std::vector<Vertex>&, std::vector<unsigned int>&, std::vector<Texture const*>&);
    ~Mesh();

    void render(const Shader*) const;
protected:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture const*> textures;
    
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    ElementBufferObject* ebo;

    void setup();
};