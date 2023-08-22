#include "Inventory.h"

Inventory::Inventory()
{
    for (int i = 0; i < 9; ++i)
    {
        slots[i] = {nullptr, 0};
    }
}

ItemStack const &Inventory::getSlot(int i) const
{
    return this->slots[i];
}

void Inventory::gain(ItemStack const& itemStack)
{
    int empty = -1;
    for (int i = 0; i < 9; ++i)
    {
        if (empty == -1 && slots[i].item == nullptr)
        {
            empty = i;
        }
        if (slots[i].item == itemStack.item)
        {
            slots[i].cnt += itemStack.cnt;
            return;
        }
    }
    if (empty != -1)
    {
        slots[empty] = itemStack;
    }
}

void Inventory::decrease(int i)
{
    if (this->slots[i].cnt >= 0)
    {
        this->slots[i].cnt -= 1;
        if (this->slots[i].cnt == 0)
        {
            this->slots[i].item = nullptr;
        }
    }
}
