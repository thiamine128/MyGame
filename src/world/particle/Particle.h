#pragma once

#include <glm/gtc/type_ptr.hpp>

class Particle
{
public:
    Particle(glm::vec3 const&, glm::vec3 const&, glm::vec3 const&);

    void tick();
    bool alive();
    glm::vec3 getPos();
    float getScale();
    glm::vec4 const& getColor() const;
protected:
    glm::vec3 prevPos, pos, velocity;
    glm::vec4 color;
    int life, maxLife;
    float prevScale, scale;
};