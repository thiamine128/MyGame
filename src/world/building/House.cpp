#include "House.h"

#include "ModelManager.h"

House::House(glm::vec3 pos) : Building(pos, AABB(pos - glm::vec3(4.0, 0.0, 4.0), pos + glm::vec3(4.0, 8.0, 4.0)))
{
    this->model = ModelManager::getModel("assets/model/house.obj");

    this->collisions.emplace_back(pos + glm::vec3(-4.0, 0.0, -4.0), pos + glm::vec3(-4.0, 8.0, 4.0));
    this->collisions.emplace_back(pos + glm::vec3(-4.0, 0.0, -4.0), pos + glm::vec3(-0.8, 8.0, -4.0));
    this->collisions.emplace_back(pos + glm::vec3(0.8, 0.0, -4.0), pos + glm::vec3(4.0, 8.0, -4.0));
    this->collisions.emplace_back(pos + glm::vec3(4.0, 0.0, -4.0), pos + glm::vec3(4.0, 8.0, 4.0));
    this->collisions.emplace_back(pos + glm::vec3(-4.0, 0.0, 4.0), pos + glm::vec3(4.0, 8.0, 4.0));
}

void House::render(const Shader* shader)
{
    glm::mat4 modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, this->pos);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(8.0));
    shader->setMat4("model", modelMatrix);
    this->model->render(shader);
}
