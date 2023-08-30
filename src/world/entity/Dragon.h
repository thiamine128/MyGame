#include "Enemy.h"

class Dragon : public Enemy
{
public:
    Dragon(World*, glm::vec3 const&);

    virtual void tick();
    virtual void updateAi();
    virtual void onDeath();
    virtual void onCollide(int);
protected:
    int action, actionTick;
    std::uniform_int_distribution<int> actionUni;
    std::uniform_real_distribution<float> bulletUni;
};