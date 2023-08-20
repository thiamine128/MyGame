#include "CropProperties.h"

#include "ModelManager.h"
CropProperties* CropProperties::potato = new CropProperties(CropType::Potato, 3, new int[4]{0, 1, 2, 3}, "assets/model/crop/potato.obj");

CropProperties::CropProperties(CropType type, int maxStage, int* stages, const char* modelPath) : type(type), maxStage(maxStage), stages(stages), modelPath(modelPath)
{
    this->model = nullptr;
}

const Mesh *CropProperties::getMesh(int day)
{
    if (this->model == nullptr)
        this->model = ModelManager::getModel(modelPath);
    return this->model->getMesh(stages[day]);
}

int CropProperties::getMaxStage() const
{
    return this->maxStage;
}

int CropProperties::getStage(int day) const
{
    return this->stages[day];
}
