#include "GUI.h"

#include "rendering/Shader.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Window.h"
#include "Game.h"

#include <iostream>

float rect[] =
{
    1.0, 1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 1.0
};

unsigned int indices[] =
{
    0, 1, 3,
    1, 2, 3
};

GUI::GUI()
{
    this->updateViewport();
    this->vao = new VertexArrayObject();
    this->vbo = new VertexBufferObject();
    this->ebo = new ElementBufferObject();
    this->vao->bind();
    this->vbo->bind();
    this->vbo->bufferDataStatic(sizeof(rect), rect);
    this->ebo->bind();
    this->ebo->bufferDataStatic(sizeof(indices), indices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    this->slotTexture = TextureManager::getTexture("assets/texture/gui/itemslot.png");
}

void GUI::render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    this->renderSlots();
    glClear(GL_DEPTH_BUFFER_BIT);
    this->renderSlotItems(Game::getInstance()->getWorld()->getPlayer()->getInventory());
}

void GUI::renderSlots()
{
    int w = this->viewport.y / 6.0;
    for (int i = 0; i < 9; ++i) {
        this->renderImage(i * w, 0, w, w, this->slotTexture);
    }
}

void GUI::renderImage(int x, int y, int w, int h, const Texture* texture)
{
    glActiveTexture(GL_TEXTURE0);
    texture->bind();
    const Shader* shader = ShaderManager::getGui();
    shader->use();
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(x, y, 0));
    model = glm::scale(model, glm::vec3(w, h, 0));
    shader->setMat4("model", model);
    this->vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GUI::renderGuiModel(int x, int y, int size, const Model* model)
{
    const Shader* shader = ShaderManager::getGuiModel();
    glm::mat4 modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size));
    shader->use();
    shader->setMat4("model", modelMatrix);
    model->render(shader);
}

void GUI::renderSlotItems(Inventory* inventory)
{
    int w = this->viewport.y / 6.0;
    for (int i = 0; i < INV_SIZE; ++i)
    {
        Item* item = inventory->getSlot(i).item;
        if (item != nullptr)
        {
            this->renderGuiModel(w / 2 + w * i, w / 16, w, ModelManager::getModel(item->getModelPath()));
        }
    }
}

void GUI::updateViewport()
{
    this->viewport.x = Window::getInstance()->getWidth();
    this->viewport.y = Window::getInstance()->getHeight();

    this->projection = glm::ortho(0.0f, this->viewport.x * 2.0f, 0.0f, this->viewport.y * 2.0f, -100.0f, 100.0f);
}

glm::vec2 const& GUI::getViewport() const
{
    return this->viewport;
}

glm::mat4 const & GUI::getProjection() const
{
    return this->projection;
}
