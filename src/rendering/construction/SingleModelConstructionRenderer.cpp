#include "SingleModelConstructionRenderer.h"

#include "Game.h"
#include "ShaderManager.h"

SingleModelConstructionRenderer::SingleModelConstructionRenderer(const Model* model)
{
    this->model = model;
}

SingleModelConstructionRenderer::~SingleModelConstructionRenderer()
{
}

void SingleModelConstructionRenderer::render(Construction* construction) const
{
    const Shader* shader = ShaderManager::getDefault();
    shader->use();
    
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, construction->getPos());
    
    shader->setMat4("model", model);
    
    Game::getInstance()->getGameRenderer()->setupViewProjection(shader);

    this->model->render(shader);
}
