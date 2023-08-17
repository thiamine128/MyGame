#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "world/Player.h"

class Camera
{
public:
    Camera();
    ~Camera();

    glm::mat4 const& getView() const;
    void setPos(glm::vec3&);
    void setCenter(glm::vec3&);
    void setUp(glm::vec3&);
    void update(Player*);
protected:
    glm::vec3 pos, center, up;
    glm::mat4 view;
};