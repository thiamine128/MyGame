#pragma once

#include "Mesh.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class InstancedRenderer
{
public:
    InstancedRenderer(const Mesh*);
    void updateModelMatrices(std::vector<glm::vec3> const&);

    void render(const Shader*);
protected:
    const Mesh* mesh;
    VertexBufferObject* vbo;
    std::vector<glm::mat4> modelMatrices;
};