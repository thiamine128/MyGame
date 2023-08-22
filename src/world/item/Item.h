#pragma once

#include <string>

#include <glm/gtc/type_ptr.hpp>

class Player;

class Item
{
public:
    Item(std::string const&, std::string const&);

    std::string const& getName() const;
    std::string const& getModelPath() const;
    glm::mat4 const& getGuiTransform() const;

    virtual void use(Player*, glm::ivec2 const&);

    static Item* hoe;
    static Item* potato;
    static Item* potatoSeeds;
    static Item* planks;
    static Item* fence;
protected:
    std::string name;
    std::string modelPath;
    glm::mat4 guiTransform;
};