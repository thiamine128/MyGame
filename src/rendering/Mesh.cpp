#include "Mesh.h"

#include <string>
#include <iostream>

Mesh::Mesh(const Texture* texture)
{
    this->textures.push_back(texture);
    
    this->setup();
}

Mesh::Mesh()
{
    this->setup();
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture const *> &textures)
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

void Mesh::render(const Shader* shader) const
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

void Mesh::renderInstanced(const Shader* shader, int amount) const
{
    for (unsigned int i = 0; i < this->textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        
        shader->setInt(("texture" + std::to_string(i)).c_str(), i);
        this->textures[i]->bind();
    }

    glActiveTexture(GL_TEXTURE0);

    this->vao->bind();
    glDrawElementsInstanced(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0, amount);
    this->vao->unbind();

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::render() const
{
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


void Mesh::quad(Vertex& v1, Vertex& v2, Vertex& v3, Vertex& v4)
{
    unsigned int st = this->vertices.size();
    this->vertices.push_back(v1);
    this->vertices.push_back(v2);
    this->vertices.push_back(v3);
    this->vertices.push_back(v4);
    this->indices.emplace_back(st);
    this->indices.emplace_back(st + 1);
    this->indices.emplace_back(st + 2);
    this->indices.emplace_back(st);
    this->indices.emplace_back(st + 2);
    this->indices.emplace_back(st + 3);
}

void Mesh::merge(const Mesh* mesh, glm::vec3 offset)
{
    int st = this->vertices.size();
    for (auto v : mesh->vertices) {
        this->vertices.emplace_back(v.position + offset, v.normal, v.texCoord);
    }
    for (auto ind : mesh->indices) {
        this->indices.emplace_back(ind + st);
    }
}

void Mesh::clear()
{
    this->vertices.clear();
    this->indices.clear();
}

void Mesh::build() const
{
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

void Mesh::setupInstancing(VertexBufferObject* vbo) const
{
    this->vao->bind();
    vbo->bind();
    for (int i = 0; i < 4; ++i) {
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * sizeof(glm::vec4)));
    }

    for (int i = 0; i < 4; ++i) {
        glVertexAttribDivisor(3 + i, 1);
    }

    this->vao->unbind();
}
