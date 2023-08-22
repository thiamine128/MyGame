#pragma once

#include "Item.h"

class ToolItem : public Item
{
public:
    ToolItem(std::string const&, std::string const&);

    virtual void use(Player*, glm::ivec2 const&);
};