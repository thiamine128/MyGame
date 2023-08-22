#include "Screen.h"

#include "rendering/WorldRenderer.h"
#include "world/item/Inventory.h"

class GameScreen : public Screen
{
public:
    GameScreen(GuiRenderer*, WorldRenderer*);

    virtual void render() const;
protected:
    WorldRenderer* worldRenderer;
    const Texture* slotTexture;
    const Texture* selectedSlotTexture;

    void renderSlots() const;
    void renderSlotItems(Inventory*) const;
};