#include "Pathfinder.h"

#include <queue>

int Pathfinder::dx[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
int Pathfinder::dy[8] = {0, 0, -1, 1, 1, -1, -1, 1};

int Pathfinder::vis[17][17];
glm::ivec2 Pathfinder::prev[17][17];

#include <iostream>

bool Pathfinder::findPath(Room* room, glm::ivec2 const& src, glm::ivec2 const& dst, std::vector<glm::ivec2>& path)
{
    memset(vis, 0, sizeof(int) * 17 * 17);
    std::queue<glm::ivec2> q;
    q.push(src);
    markVis(src.x, src.y);
    
    while (!q.empty() && getVis(dst.x, dst.y) == 0)
    {
        auto cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            auto npos = cur + glm::ivec2(dx[i], dy[i]);
            if (room->getBlock(npos.x, npos.y) == 0 && getVis(npos.x, npos.y) == 0)
            {
                markVis(npos.x, npos.y);
                setPrev(npos.x, npos.y, cur);
                q.push(npos);
            }
        }

        for (int i = 4; i < 8; ++i)
        {
            auto npos = cur + glm::ivec2(dx[i], dy[i]);
            if (room->getBlock(npos.x, npos.y) == 0 && room->getBlock(cur.x + dx[i], cur.y) == 0 && room->getBlock(cur.x, cur.y + dy[i]) == 0)
            {
                if (getVis(npos.x, npos.y) == 0)
                {
                    markVis(npos.x, npos.y);
                    setPrev(npos.x, npos.y, cur);
                    q.push(npos);
                }
            }
        }
    }

    path.clear();
    if (getVis(dst.x, dst.y))
    {
        auto cur = dst;
        while (cur != src)
        {
            path.push_back(cur);
            cur = getPrev(cur.x, cur.y);
        }
        path.push_back(src);
        std::reverse(path.begin(), path.end());
        return true;
    }
    return false;
}

void Pathfinder::markVis(int x, int y)
{
    vis[x + 7][y + 7] = 1;
}

int Pathfinder::getVis(int x, int y)
{
    return vis[x + 7][y + 7];
}

void Pathfinder::setPrev(int x, int y, glm::ivec2 v)
{
    prev[x + 7][y + 7] = v;
}

glm::ivec2 const& Pathfinder::getPrev(int x, int y)
{
    return prev[x + 7][y + 7];
}
