#pragma once

#include "ItemStack.h"

#define INV_SIZE 9

class Inventory
{
public:
    Inventory();

    ItemStack const& getSlot(int) const;
    void gain(ItemStack const&);
protected:
    ItemStack slots[INV_SIZE];
};