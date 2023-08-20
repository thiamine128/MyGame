#pragma once

#include "TileType.h"

#include <unordered_map>
#include <string>
class Tile
{
public:
    Tile();

    TileType getType() const;
    void setType(TileType);
protected:
    TileType type;
};