#include "rendering/Camera.h"

Camera::Camera()
{
    this->pos = glm::vec3(8.0f, 0.0f, 8.0f);
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

glm::mat4 Camera::getView() const&
{
    return glm::lookAt(pos, center, up);
}
