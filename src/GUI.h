#pragma once

#include "rendering/Texture.h"
#include "rendering/VertexArrayObject.h"
#include "rendering/VertexBufferObject.h"
#include "rendering/ElementBufferObject.h"
#include "world/item/Inventory.h"
class Model;
#include <glm/gtc/type_ptr.hpp>

class GUI
{
public:
    GUI();

    void render();
    void renderSlots();
    void renderImage(int, int, int, int, const Texture*);
    void renderGuiModel(int, int, int, const Model*);
    void renderSlotItems(Inventory*);
    void updateViewport();
    glm::vec2 const& getViewport() const;
    glm::mat4 const& getProjection() const;
protected:
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    ElementBufferObject* ebo;
    const Texture* slotTexture;
    glm::vec2 viewport;
    glm::mat4 projection;
};