#include "Store.h"

#include "ModelManager.h"

Store::Store(glm::vec3 pos) : Building(pos, AABB(pos - glm::vec3(2.0, 0.0, 2.0), pos + glm::vec3(2.0, 8.0, 2.0)))
{
    this->model = ModelManager::getModel("assets/model/store.obj");
    this->collisions.push_back(this->aabb);
}

void Store::render(const Shader* shader)
{
    glm::mat4 modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, this->pos);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(4.0));
    shader->setMat4("model", modelMatrix);
    this->model->render(shader);
}
