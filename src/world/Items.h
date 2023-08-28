#pragma once

#include <string>

class Player;

class Item
{
public:
    Item(std::string const&, std::string const&);

    std::string const& getModelPath() const;

    static void onPickup(Item*, Player*);

    static void init();
    static Item* m[128];
    static Item* torchwood;
    static Item* ice;
    static Item* arrow;
    static Item* milk;
    static Item* glass;
protected:
    std::string name;
    std::string modelPath;
};