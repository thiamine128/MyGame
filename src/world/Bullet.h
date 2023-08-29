#pragma once

#include "Entity.h"
#include "rendering/Model.h"
#include "Items.h"

#include <vector>
#include <bitset>
#include <unordered_set>

class Bullet : public Entity
{
public:
    Bullet(World*, glm::vec3 const&, glm::vec3 const&, float);

    virtual void render(const Shader*) const;
    virtual void tick();
    virtual void onCollide(int);
    virtual void onRemove();

    void onHit(Entity*);
    void setFire();
    void setFrozen();
    void setPierce();
    void setTracking();
    void addDamage(float);
    bool isFire() const;
    bool isFrozen() const;
    bool isPierce() const;
    bool isTracking() const;
    void doDamage(Entity*);

    static void apply(Bullet*, Player*, std::vector<Item*> const&);
protected:
    float range;
    float size;
    float damage;
    float totDist;
    const Model* model;
    const Model* fire;
    glm::vec3 initialPos;
    glm::vec4 color;
    std::bitset<128> flag;
    std::unordered_set<Entity*> pierced;
    std::uniform_real_distribution<float> uni;
};

class EnemyBullet : public Entity
{
public:
    EnemyBullet(World*, glm::vec3 const&, glm::vec3 const&, float, float, glm::vec4 const&);

    virtual void render(const Shader*) const;
    virtual void tick();
    virtual void onCollide(int);
    virtual void onRemove();

protected:
    glm::vec4 color;
    float size;
    glm::vec3 initialPos;
    float range;
    std::uniform_real_distribution<float> uni;
};