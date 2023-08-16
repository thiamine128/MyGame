#include "rendering/Mesh.h"

#include <string>
#include <iostream>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture const*>& textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->setup();
}

Mesh::~Mesh()
{
    delete this->vao;
    delete this->vbo;
    delete this->ebo;
}

void Mesh::render(Shader* shader) const
{
    for (unsigned int i = 0; i < this->textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        
        shader->setInt(("texture" + std::to_string(i)).c_str(), i);
        this->textures[i]->bind();
    }

    glActiveTexture(GL_TEXTURE0);

    this->vao->bind();
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    this->vao->unbind();

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setup()
{
    this->vao = new VertexArrayObject();
    this->vbo = new VertexBufferObject();
    this->ebo = new ElementBufferObject();

    this->vao->bind();
    this->vbo->bind();
    this->ebo->bind();

    this->vbo->bufferDataStatic(this->vertices.size() * sizeof(Vertex), &(this->vertices[0]));
    this->ebo->bufferDataStatic(this->indices.size() * sizeof(unsigned int), &(this->indices[0]));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));

    this->vao->unbind();
}
