#include "RigUnit_EndLookAt_Item.h"

FRigUnit_EndLookAt_Item::FRigUnit_EndLookAt_Item() {
    this->bOptionalUpAxis = false;
    this->Layer = EEndLookAtLayer::Body;
    this->Weight = 0.00f;
    this->UpRate = 0.00f;
    this->DownRate = 0.00f;
    this->IgnoreAngle = 0.00f;
    this->BlendTimeBiasMin = 0.00f;
    this->BlendTimeBiasMax = 0.00f;
    this->BlendDelayTimeMin = 0.00f;
    this->BlendDelayTimeMax = 0.00f;
}

