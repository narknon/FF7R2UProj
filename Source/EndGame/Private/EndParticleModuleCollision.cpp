#include "EndParticleModuleCollision.h"

UEndParticleModuleCollision::UEndParticleModuleCollision() {
    this->bSupported3DDrawMode = true;
    this->CollisionTypes.AddDefaulted(3);
    this->bDropDetail = false;
    this->m_HitOffsetNormalScale = 1.00f;
    this->m_FreezeTranslationVelocityLength = 1.00f;
}


