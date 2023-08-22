#pragma once

#include "rendering/Texture.h"
#include "rendering/VertexArrayObject.h"
#include "rendering/VertexBufferObject.h"
#include "rendering/ElementBufferObject.h"
#include "world/item/Inventory.h"

class Model;

#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

struct Character
{
    Texture* texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

class GUI
{
public:
    GUI();

    void render();
    void renderSlots();
    void renderImage(int, int, int, int, const Texture*);
    void renderGuiModel(int, int, int, const Model*, glm::mat4 const&);
    void renderSlotItems(Inventory*);
    void updateViewport();
    void renderText(float, float, float, std::string const&);
    glm::vec2 const& getViewport() const;
    glm::mat4 const& getProjection() const;
protected:
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    ElementBufferObject* ebo;
    const Texture* slotTexture;
    const Texture* selectedSlotTexture;
    glm::vec2 viewport;
    glm::mat4 projection;
    std::unordered_map<char, Character> characters;

    void setupRect();
    void initFont();
};