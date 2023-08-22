#include "GameScreen.h"

#include "TextureManager.h"
#include "ModelManager.h"

GameScreen::GameScreen(GuiRenderer* guiRenderer, WorldRenderer* worldRenderer) : Screen(guiRenderer), worldRenderer(worldRenderer)
{
    this->slotTexture = TextureManager::getTexture("assets/texture/gui/itemslot.png");
    this->selectedSlotTexture = TextureManager::getTexture("assets/texture/gui/itemslot_selected.png");
}

void GameScreen::render() const
{
    this->worldRenderer->render();

    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    this->renderSlots();
}

void GameScreen::renderSlots() const
{
    glm::vec2 const& viewport = this->guiRenderer->getViewport();
    int w = viewport.y / 10.0;
    Player* player = this->worldRenderer->getWorld()->getPlayer();
    for (int i = 0; i < 9; ++i)
    {
        if (i == player->getSelectedSlot())
            this->guiRenderer->renderImage(i * w, 0, w, w, this->selectedSlotTexture);
        else
            this->guiRenderer->renderImage(i * w, 0, w, w, this->slotTexture);
    }
    glClear(GL_DEPTH_BUFFER_BIT);
    Inventory* inventory = player->getInventory();
    this->renderSlotItems(inventory);
    glClear(GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < 9; ++i)
    {
        int cnt = inventory->getSlot(i).cnt;
        if (cnt > 1)
        {
            this->guiRenderer->renderText(w + w * i - w / 3, w / 6, 0.4f, std::to_string(cnt));
        }
    }
}


void GameScreen::renderSlotItems(Inventory* inventory) const
{
    glm::vec2 const& viewport = this->guiRenderer->getViewport();
    int w = viewport.y / 10.0;
    for (int i = 0; i < 9; ++i)
    {
        Item* item = inventory->getSlot(i).item;
        if (item != nullptr)
        {
            this->guiRenderer->renderGuiModel(w / 2 + w * i, w / 2, w, ModelManager::getModel(item->getModelPath()), item->getGuiTransform());
        }
    }
}