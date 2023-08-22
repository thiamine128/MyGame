#pragma once

#include "Item.h"
#include "world/construction/ConstructionType.h"

class ConstructionItem : public Item
{
public:
    ConstructionItem(std::string const&, std::string const&, ConstructionType);

    virtual void use(Player*, glm::ivec2 const&);
protected:
    ConstructionType constructionType;
};