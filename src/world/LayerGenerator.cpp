#include "LayerGenerator.h"

#include <queue>
#include <random>
#include <iostream>

Room* LayerGenerator::m[13][13];
int LayerGenerator::dx[4] = {-1, 0, 0, 1};
int LayerGenerator::dy[4] = {0, -1, 1, 0};

Room *LayerGenerator::generateRooms(World* world, int num, int stage)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    int roomCnt = 4;
    if (stage == 2)
    {
        roomCnt = 3;
    } else if (stage == 3)
    {
        roomCnt = 2;
    }
    std::uniform_int_distribution<int> uni(0, 100);
    std::uniform_int_distribution<int> layout(1, roomCnt);
    std::priority_queue<std::tuple<int, int, int>> pq;
    pq.emplace(uni(rng), 6, 6);
    int cnt = 1;
    
    while (cnt < num && !pq.empty())
    {
        auto c = pq.top();
        pq.pop();
        int x = std::get<1>(c), y = std::get<2>(c);
        std::string layoutId = "0";
        int flag = 0;
        if (cnt + 1 == num)
        {
            layoutId = "boss", flag |= 1;
        } else if (cnt + 2 == num)
        {
            layoutId = "item", flag |= 2;
        }
        else if (cnt > 1)
            layoutId = std::to_string(layout(rng));
        
        m[x][y] = new Room(world, "assets/rooms/" + std::to_string(stage) + "/" + layoutId + ".layout", stage, flag);
        ++cnt;
        if (valid(x, y))
        {
            for (int i = 0; i < 4; ++i)
            {
                if (valid(x + dx[i], y + dy[i]) && m[x + dx[i]][y + dy[i]] == nullptr)
                {
                    pq.emplace(uni(rng), x + dx[i], y + dy[i]);
                }
            }
        }
    }

    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            if (m[i][j] != nullptr)
            {
                for (int k = 0; k < 4; ++k)
                {
                    int x = i + dx[k], y = j + dy[k];
                    if (valid(x, y) && m[x][y] != nullptr)
                    {
                        m[i][j]->open(k);
                        m[i][j]->setConnect(k, m[x][y]);
                    }
                }
            }
        }
    }
   
    return m[6][6];
}

bool LayerGenerator::valid(int x, int y)
{
    return x >= 0 && x < 13 && y >= 0 && y < 13;
}

void LayerGenerator::clear()
{
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            if (m[i][j] != nullptr)
            {
                delete m[i][j];
                m[i][j] = nullptr;
            }
        }
    }
}
