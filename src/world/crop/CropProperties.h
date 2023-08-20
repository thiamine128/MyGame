#pragma once

#include "rendering/Model.h"

enum class CropType 
{
    Potato = 1
};

class CropProperties
{
public:
    CropProperties(CropType, int, int*, const char*);

    const Mesh* getMesh(int);
    int getMaxStage() const;
    int getStage(int) const;
    static CropProperties* potato;
protected:
    CropType type;
    int maxStage;
    const char* modelPath;
    const Model* model;
    int* stages;
};