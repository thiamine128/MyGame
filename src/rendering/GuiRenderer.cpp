#include "GuiRenderer.h"

#include "rendering/Shader.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Window.h"
#include "Game.h"

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

float rect[] =
{
    1.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 0.0, 0.0
};

unsigned int indices[] =
{
    0, 1, 3,
    1, 2, 3
};

GuiRenderer::GuiRenderer()
{
    this->updateViewport();
    
    this->setupRect();
    
    this->initFont();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GuiRenderer::renderImage(int x, int y, int w, int h, const Texture* texture)
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

void GuiRenderer::renderGuiModel(int x, int y, int size, const Model* model, glm::mat4 const& modelMatrix)
{
    const Shader* shader = ShaderManager::getGuiModel();
    glm::mat4 finalModel = glm::mat4(1.0);
    finalModel = glm::translate(finalModel, glm::vec3(x, y, 0));
    finalModel = glm::scale(finalModel, glm::vec3(size));
    finalModel = finalModel * modelMatrix;
    shader->use();
    shader->setMat4("model", finalModel);
    model->render(shader);
}

void GuiRenderer::updateViewport()
{
    this->viewport.x = Window::getInstance()->getWidth();
    this->viewport.y = Window::getInstance()->getHeight();

    this->projection = glm::ortho(0.0f, this->viewport.x, 0.0f, this->viewport.y, -100.0f, 100.0f);
}

void GuiRenderer::renderText(float x, float y, float size, std::string const& text)
{
    const Shader* shader = ShaderManager::getText();
    shader->use();
    glActiveTexture(GL_TEXTURE0);
    this->vao->bind();
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); ++c)
    {
        Character ch = characters[*c];
        float xPos = x + ch.bearing.x * size;
        float yPos = y - (ch.size.y - ch.bearing.y) * size;
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(xPos, yPos, 0.0));
        model = glm::scale(model, glm::vec3(ch.size.x * size, ch.size.y * size, 0));

        shader->setMat4("model", model);
        ch.texture->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        x += (ch.advance >> 6) * size;
    }
    
}

glm::vec2 const& GuiRenderer::getViewport() const
{
    return this->viewport;
}

glm::mat4 const & GuiRenderer::getProjection() const
{
    return this->projection;
}

void GuiRenderer::setupRect()
{
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
}

void GuiRenderer::initFont()
{
    FT_Library ft;
    FT_Face face;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "Failed to load freetype." << std::endl;
    }
    if (FT_New_Face(ft, "assets/fonts/arial.ttf", 0, &face))
    {
        std::cout << "Failed to load font." << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 1; c < 128; ++c)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "Failed to load char." << std::endl;
            continue;
        }

        Texture* texture = new Texture();
        texture->bind();
        texture->glyph(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);
        characters[c] = {texture, {face->glyph->bitmap.width, face->glyph->bitmap.rows}, {face->glyph->bitmap_left, face->glyph->bitmap_top}, static_cast<unsigned int>(face->glyph->advance.x)};
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}