#include "HSFLipMapShape.h"

FHSFLipMapShape::FHSFLipMapShape() {
    this->AudioMin = 0.00f;
    this->AudioMax = 0.00f;
    this->AudioPower = 0.00f;
    this->bBlend = false;
    this->BlendIn = 0.00f;
    this->BlendOut = 0.00f;
    this->bRandomize = false;
    this->bRandomizePerChannel = false;
    this->RandomMin = 0.00f;
    this->RandomMax = 0.00f;
    this->bForceShape = false;
}

