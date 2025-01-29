#include "VfxParticleModuleTypeDataTrajectory.h"

UVfxParticleModuleTypeDataTrajectory::UVfxParticleModuleTypeDataTrajectory() {
    this->m_MaxTrailCount = 1;
    this->m_RenderAxisOption = EVfxTrajectoryRenderAxisOption::EVTRAO_RightVector;
    this->m_fTextureTileDistance = 100.00f;
    this->m_bRenderGeometry = true;
    this->m_bApplyMatrixScaleVelocity = false;
    this->m_bIgnoreLimitTrailLength = false;
    this->m_fTrailDivDistance = 10.00f;
    this->m_BufferCount = 16;
    this->m_UpdateBufferFPS = 30;
    this->m_bDebugDrawBufferPoint = false;
    this->m_bDebugDrawPointCoordinate = false;
    this->m_bDebugDrawPolygonLine = false;
    this->m_bDebugDrawInterpPoint = false;
    this->m_bDebugDrawTangent = false;
}


