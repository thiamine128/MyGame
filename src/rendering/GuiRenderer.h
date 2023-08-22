#pragma once

#include "rendering/glhelper.h"
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

class GuiRenderer
{
public:
    GuiRenderer();
    
    void renderImage(int, int, int, int, const Texture*);
    void renderGuiModel(int, int, int, const Model*, glm::mat4 const&);
    void updateViewport();
    void renderText(float, float, float, std::string const&);
    glm::vec2 const& getViewport() const;
    glm::mat4 const& getProjection() const;
protected:
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    ElementBufferObject* ebo;
    glm::vec2 viewport;
    glm::mat4 projection;
    std::unordered_map<char, Character> characters;

    void setupRect();
    void initFont();
};