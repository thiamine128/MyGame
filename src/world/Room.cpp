#include "Room.h"

#include "rendering/glhelper.h"
#include "ModelManager.h"
#include "Enemy.h"
#include "World.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

int Room::dx[4] = {-1, 0, 0, 1};
int Room::dy[4] = {0, -1, 1, 0};

Room::Room(World* world, std::string const& layout, int stage, int roomFlag) : world(world), rng(rd()), heartDrop(0, 100), roomFlag(roomFlag)
{
    this->aabbs.push_back({{-9.0f, 0.0f, -9.0f}, {9.0f, 0.0f, 9.0f}});

    this->setupModels(stage);

    for (int i = 0; i < 4; ++i)
        next[i] = nullptr, door[i] = 0;
    
    this->setup(layout);
    this->completeFlag = 0;
}

Room::~Room()
{
    for (auto e : entities)
        delete e;
}

void Room::render(const Shader* shader)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(64.0f));
    shader->setMat4("model", modelMatrix);
    this->blockModels[0]->render(shader);

    for (auto e : entities)
    {
        e->render(shader);
    }

    for (int i = -7; i <= 7; ++i)
    {
        for (int j = -7; j <= 7; ++j)
        {
            if (this->getBlock(i, j) != 0)
            {
                glm::mat4 modelMat = glm::mat4(1.0);
                modelMat = glm::translate(modelMat, glm::vec3(i + 0.5f, 0, j + 0.5f));
                shader->setMat4("model", modelMat);
                this->blockModels[this->getBlock(i, j)]->render(shader);
            }
        }
    }

    for (auto p : particles)
    {
        glm::vec3 const& pos = p->getPos();
        glm::mat4 modelMat = glm::mat4(1.0);
        modelMat = glm::translate(modelMat, pos);
        modelMat = glm::scale(modelMat, glm::vec3(p->getScale()));
        modelMat = glm::scale(modelMat, glm::vec3(0.3f));
        shader->setMat4("model", modelMat);
        shader->setVec4("color", p->getColor());
        ModelManager::getModel("assets/models/sphere.obj")->render(shader);
        shader->setVec4("color", glm::vec4(1.0));
    }
}

bool Room::checkCollision(AABB const& aabb) const
{
    for (auto e : aabbs) {
        if (e.collideWith(aabb))
            return true;
    }
    for (int i = -7; i <= 7; ++i)
    {
        for (int j = -7; j <= 7; ++j)
        {
            if (this->getBlock(i, j) != 0)
            {
                AABB blockAABB = {{i, 0, j}, {i + 1, 2, j + 1}};
                if (blockAABB.collideWith(aabb))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

Entity* Room::hitEnermy(AABB const& aabb) const
{
    for (auto e : entities)
    {
        if (e->isEnemy() && e->getAABB().collideWith(aabb))
        {
            return e;
        }
    }
    return nullptr;
}

void Room::tick()
{
    bool hasEnermy = false;
    for (int i = entities.size() - 1; i >= 0; --i)
    {
        entities[i]->tick();
        if (entities[i]->shouldRemove())
        {
            delete entities[i];
            entities.erase(entities.begin() + i);
        } else if (entities[i]->isEnemy())
        {
            hasEnermy = true;
        }
    }
    for (int i = particles.size() - 1; i >= 0; --i)
    {
        particles[i]->tick();
        if (!particles[i]->alive())
        {
            delete particles[i];
            particles.erase(particles.begin() + i);
        }
    }
    if (this->completeFlag == 0 && !hasEnermy)
    {
        this->onComplete();
        this->completeFlag = 1;
    }
    glm::vec3 ppos = world->getPlayer()->getPos();
    if (ppos.x < -7.0f)
    {
        this->world->setRoom(next[0]);
        this->world->getPlayer()->setPos(glm::vec3(5.5f, 0.0f, 0.0f));
    } else if (ppos.x > 7.0f)
    {
        this->world->setRoom(next[3]);
        this->world->getPlayer()->setPos(glm::vec3(-5.5f, 0.0f, 0.0f));
    } else if (ppos.z < -7.0f)
    {
        this->world->setRoom(next[1]);
        this->world->getPlayer()->setPos(glm::vec3(0.0f, 0.0f, 5.5f));
    } else if (ppos.z > 7.0f)
    {
        this->world->setRoom(next[2]);
        this->world->getPlayer()->setPos(glm::vec3(0.0f, 0.0f, -5.5f));
    }
}

void Room::addEntity(Entity* entity)
{
    this->entities.push_back(entity);
}

void Room::setBlock(int x, int y, int b)
{
    this->block[x + 7][y + 7] = b;
}

int Room::getBlock(int x, int y) const
{
    return this->block[x + 7][y + 7];
}

void Room::setup(std::string const& layout)
{
    for (int i = -7; i <= 7; ++i)
    {
        for (int j = -7; j <= 7; ++j)
        {
            if (i == -7 || i == 7 || j == -7 || j == 7)
            {
                this->setBlock(i, j, 1);
            } else
            {
                this->setBlock(i, j, 0);
            }
        }
    }

    this->loadLayout(layout);
}

void Room::setupModels(int stage)
{
    switch (stage)
    {
    case 1:
        this->blockModels[0] = ModelManager::getModel("assets/models/scene.obj");
        this->blockModels[1] = ModelManager::getModel("assets/models/tree.obj");
        this->blockModels[2] = ModelManager::getModel("assets/models/rock.obj");
        this->blockModels[3] = ModelManager::getModel("assets/models/mushroom.obj");
        break;
    case 2:
        this->blockModels[0] = ModelManager::getModel("assets/models/cave.obj");
        this->blockModels[1] = ModelManager::getModel("assets/models/cavewall.obj");
        this->blockModels[2] = ModelManager::getModel("assets/models/rock.obj");
        this->blockModels[3] = ModelManager::getModel("assets/models/mushroom.obj");
        break;
    case 3:
        this->blockModels[0] = ModelManager::getModel("assets/models/street.obj");
        this->blockModels[1] = ModelManager::getModel("assets/models/cone.obj");
        this->blockModels[2] = ModelManager::getModel("assets/models/rock.obj");
        this->blockModels[3] = ModelManager::getModel("assets/models/mushroom.obj");
    default:
        break;
    }
}

void Room::open(int dir)
{
    door[dir] = 1;
    if (dx[dir] == 0)
        for (int i = -1; i <= 1; ++i)
            this->setBlock(i, 7 * dy[dir], 3);
    if (dy[dir] == 0)
        for (int i = -1; i <= 1; ++i)
            this->setBlock(7 * dx[dir], i, 3);
}

void Room::setConnect(int dir, Room* room)
{
    this->next[dir] = room;
}

void Room::getEnemiesWithin(std::vector<Entity*>& entities, AABB const& aabb)
{
    for (auto e : this->entities)
    {
        if (e->getAABB().collideWith(aabb) && e->isEnemy())
        {
            entities.emplace_back(e);
        }
    }
}

void Room::loadLayout(std::string const& layout)
{
    std::ifstream f;
    std::cout << layout << std::endl;
    f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f.open(layout);

    std::stringstream fs;
    fs << f.rdbuf();

    f.close();

    int b;
    for (int i = -6; i <= 6; ++i)
    {
        for (int j = -6; j <= 6; ++j)
        {
            fs >> b;
            this->setBlock(i, j, b);
        }
    }

    int t, d;
    float x, y;
    char s;
    while (fs >> t)
    {
        fs >> s >> d >> x >> y;
        this->spawnEntity(t, d, x, y);
    }
}

void Room::spawnEntity(int id, int ex, float x, float y)
{
    switch (id)
    {
    case 0:
        this->addEntity(new ItemEntity(this->world, glm::vec3(x, 0.0, y), ex));
        break;
    case 1:
        this->addEntity(new Zombie(this->world, glm::vec3(x, 0.0, y), ex));
        break;
    case 2:
        this->addEntity(new SlimeBoss(this->world, glm::vec3(x, 0.0, y)));
        break;
    case 3:
        this->addEntity(new EntranceEntity(this->world, glm::vec3(x, 0.0, y)));
        break;
    case 4:
        this->addEntity(new ZombieShooter(this->world, glm::vec3(x, 0.0, y), ex));
        break;
    case 5:
        this->addEntity(new HeartEntity(this->world, glm::vec3(x, 0.0, y)));
        break;
    case 6:
        this->addEntity(new BabyPlum(this->world, glm::vec3(x, 0.0, y)));
        break;
    default:
        break;
    }
}

void Room::onComplete()
{
    for (int dir = 0; dir < 4; ++dir)
    {
        if (door[dir])
        {
            if (dx[dir] == 0)
                for (int i = -1; i <= 1; ++i)
                    this->setBlock(i, 7 * dy[dir], 0);
            if (dy[dir] == 0)
                for (int i = -1; i <= 1; ++i)
                    this->setBlock(7 * dx[dir], i, 0);
        }
    }

    if (heartDrop(rng) < 40)
    {
        Player* player = world->getPlayer();
        auto pos = findSpace(floor(player->getPos().x), floor(player->getPos().y));
        this->spawnEntity(5, 0, pos.x, pos.y);

    }
}

void Room::addParticle(glm::vec3 const& pos, glm::vec3 const& velocity, glm::vec3 const& color)
{
    addParticle(pos, velocity, color, 12);
}

void Room::addParticle(glm::vec3 const& pos, glm::vec3 const& velocity, glm::vec3 const& color, int life)
{
    particles.emplace_back(new Particle(pos, velocity, color, life));

}

bool Room::isBossRoom() const
{
    return roomFlag & 1;
}

Item *Room::getNearestItem() const
{
    Item* ret = nullptr;
    float dist = 100.0f;
    for (auto i : entities)
    {
        if (i->isItem())
        {
            if (glm::length(i->getPos() - world->getPlayer()->getPos()) < dist)
            {
                dist = glm::length(i->getPos() - world->getPlayer()->getPos());
                ret = ((ItemEntity*) i)->getItem();
            }
        }
    }
    return ret;
}

Entity *Room::findNearestEnemy() const
{
    double dist = 400.0f;
    Entity* ret = nullptr;
    for (auto e : entities)
    {
        if (e->isEnemy() && glm::length(e->getPos() - world->getPlayer()->getPos()) < dist)
        {
            dist = glm::length(e->getPos() - world->getPlayer()->getPos());
            ret = e;
        }
    }
    return ret;
}

glm::ivec2 Room::findSpace(int x, int y)
{
    int dist = 400;
    glm::ivec2 ret = glm::ivec2(0);
    for (int i = -7; i <= 7; ++i)
    {
        for (int j = -7; j <= 7; ++j)
        {
            if (getBlock(i, j) == 0)
            {
                int dx = i - x, dy = j - y;
                int d = dx * dx + dy * dy;
                if (d >= 5 && d < dist)
                {
                    dist = d;
                    ret = glm::ivec2(i, j);
                }
            }
        }
    }
    return ret;
}
