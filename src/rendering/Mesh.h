#pragma once

class Vertex;
class Texture;
class Shader;
class VertexArrayObject;
class VertexBufferObject;
class ElementBufferObject;

#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Mesh
{
public:
    Mesh(const Texture* texture);
    Mesh();
    Mesh(std::vector<Vertex>&, std::vector<unsigned int>&, std::vector<Texture const*>&);
    ~Mesh();

    void render(const Shader*) const;
    void renderInstanced(const Shader*, int) const;
    void render() const;

    void quad(Vertex&, Vertex&, Vertex&, Vertex&);
    void merge(const Mesh*, glm::vec3);
    void clear();
    void build() const;
    void setupInstancing(VertexBufferObject*) const;
protected:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture const*> textures;
    
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    ElementBufferObject* ebo;

    void setup();
};