#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    glm::mat4 getView() const&;
    void setPos(glm::vec3&);
    void setCenter(glm::vec3&);
    void setUp(glm::vec3&);
protected:
    glm::vec3 pos, center, up;
};