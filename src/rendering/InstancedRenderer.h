#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "VertexBufferObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class InstancedRenderer
{
public:
    InstancedRenderer(const Mesh*);
    void reset();
    void addInstance(glm::vec3);
    void updateModelMatrices();

    void render(const Shader*);
protected:
    const Mesh* mesh;
    VertexBufferObject* vbo;
    std::vector<glm::mat4> modelMatrices;
    std::vector<glm::vec3> positions;
};