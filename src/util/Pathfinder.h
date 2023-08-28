#pragma once

#include "world/Room.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>

class Pathfinder
{
public:
    static bool findPath(Room*, glm::ivec2 const&, glm::ivec2 const&, std::vector<glm::ivec2>&);
protected:
    static int dx[8];
    static int dy[8];
    static int vis[17][17];
    static glm::ivec2 prev[17][17];

    static void markVis(int, int);
    static int getVis(int, int);
    static void setPrev(int, int, glm::ivec2);
    static glm::ivec2 const& getPrev(int, int);
};