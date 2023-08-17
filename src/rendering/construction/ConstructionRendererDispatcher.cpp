#include "ConstructionRendererDispatcher.h"

#include "ModelManager.h"
#include "SingleModelConstructionRenderer.h"

void ConstructionRendererDispatcher::init()
{
    this->entries[ConstructionType::Tree] = new SingleModelConstructionRenderer(ModelManager::getModel("assets/model/tree.obj"));
}

void ConstructionRendererDispatcher::render(Construction* construction)
{
    ConstructionRenderer* renderer = this->entries[construction->getType()];
    if (renderer != nullptr) {
        renderer->render(construction);
    }
}
