#include "InstancedRenderer.h"

InstancedRenderer::InstancedRenderer(const Mesh* mesh)
{
    this->mesh = mesh;
    this->vbo = new VertexBufferObject();
    this->mesh->setupInstancing(this->vbo);
}

void InstancedRenderer::reset()
{
    this->positions.clear();
}

void InstancedRenderer::addInstance(glm::vec3 pos)
{
    this->positions.push_back(pos);
}

void InstancedRenderer::updateModelMatrices()
{
    modelMatrices.clear();
    for (auto p : positions)
    {
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, p);
        modelMatrices.push_back(model);
    }
    this->vbo->bind();
    this->vbo->bufferDataStatic(this->modelMatrices.size() * sizeof(glm::mat4), &modelMatrices[0]);
}

void InstancedRenderer::render(const Shader* shader)
{
    mesh->renderInstanced(shader, modelMatrices.size());
}
