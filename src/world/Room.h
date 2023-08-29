#pragma once

#include "rendering/Model.h"
#include "world/Entity.h"

#include <vector>
#include <random>
#include "particle/Particle.h"

class World;

class Room
{
public:
    Room(World*, std::string const&, int, int);
    ~Room();

    void render(const Shader*);
    bool checkCollision(AABB const&) const;
    Entity* hitEnermy(AABB const&) const;
    void tick();
    void addEntity(Entity*);
    void setBlock(int, int, int);
    int getBlock(int, int) const;
    void setup(std::string const&);
    void setupModels(int);
    void open(int);
    void setConnect(int, Room*);
    void getEnemiesWithin(std::vector<Entity*>&, AABB const&);
    void loadLayout(std::string const&);
    void spawnEntity(int, int, float, float);
    void onComplete();
    void addParticle(glm::vec3 const&, glm::vec3 const&, glm::vec3 const&);
    void addParticle(glm::vec3 const&, glm::vec3 const&, glm::vec3 const&, int);
    bool isBossRoom() const;
    Item* getNearestItem() const;
    Entity* findNearestEnemy() const;
    glm::ivec2 findSpace(int, int);
protected:
    int block[15][15];
    World* world;
    const Model* blockModels[16];
    Room* next[4];
    int door[4];
    std::vector<AABB> aabbs;
    std::vector<Entity*> entities;
    std::vector<Particle*> particles;
    std::random_device rd;
    std::mt19937 rng;
    std::uniform_int_distribution<int> heartDrop;
    int roomFlag;

    int completeFlag;

    static int dx[4];
    static int dy[4];
};