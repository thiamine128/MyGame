#include "Entity.h"

class HeartEntity : public Entity
{
public:
    HeartEntity(World*, glm::vec3 const&);

    virtual void tick();
};