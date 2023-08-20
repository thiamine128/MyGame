#include "Tile.h"

Tile::Tile()
{
    this->type = TileType::Ground;
}

TileType Tile::getType() const
{
    return this->type;
}

void Tile::setType(TileType type)
{
    this->type = type;
}
