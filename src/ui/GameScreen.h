#include "Screen.h"

#include "rendering/WorldRenderer.h"

class GameScreen : public Screen
{
public:
    GameScreen(GuiRenderer*, WorldRenderer*);

    virtual void render() const;
    virtual bool handleClick(int, int) const;
    virtual void handleKeyPress(int);
protected:
    WorldRenderer* worldRenderer;
};