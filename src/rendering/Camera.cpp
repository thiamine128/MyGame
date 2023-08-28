#include "Camera.h"

#include "world/Player.h"

Camera::Camera()
{
    this->pos = glm::vec3(0.0f, 8.0f, -8.0f);
    this->center = glm::vec3(0.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
}

void Camera::setPos(glm::vec3& value)
{
    this->pos = value;
}

void Camera::setCenter(glm::vec3& value)
{
    this->center = value;
}

void Camera::setUp(glm::vec3& value)
{

    this->up = value;
}

void Camera::update(Player* player)
{
    this->pos = glm::vec3(0.0) + glm::vec3(0.0, 16.0, -6.0);
    this->center = glm::vec3(0.0);
    this->view = glm::lookAt(pos, center, up);
}

glm::vec3 Camera::getPos() const
{
    return this->pos;
}

glm::vec3 Camera::getCenter() const
{
    return this->center;
}

glm::mat4 const& Camera::getView() const
{
    return this->view;
}
