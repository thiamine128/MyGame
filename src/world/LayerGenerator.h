#pragma once

#include "Room.h"

class LayerGenerator
{
public:
    static Room* generateRooms(World*, int, int);
    static bool valid(int, int);
    static void clear();

    static Room* m[13][13];
    static int dx[4];
    static int dy[4];
};