#pragma once

#include <glm/gtc/type_ptr.hpp>

class Player
{
public:
    Player();
    ~Player();

    glm::vec3 getPosFrame() const;
    glm::vec3 getPos() const;
    glm::vec3 getVelocity() const;
    void setVelocity(glm::vec3 const&);
    void tick();
protected:
    glm::vec3 pos;
    glm::vec3 prevPos;
    glm::vec3 velocity;
};