#pragma once

#include "Item.h"

class SeedItem : public Item
{
public:
    SeedItem(std::string const&, std::string const&);

    virtual void use(Player*, glm::ivec2 const&);
};