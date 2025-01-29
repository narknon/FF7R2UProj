#include "EndBonamikBoxScaleGroupParamsComponent.h"

UEndBonamikBoxScaleGroupParamsComponent::UEndBonamikBoxScaleGroupParamsComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_Preset = NULL;
    this->m_ChangeInnerCone = false;
    this->m_InnerConeScale = 0.00f;
    this->m_ChangeOuterCone = false;
    this->m_OuterConeScale = 0.00f;
    this->m_ChangeLocalForce = false;
    this->m_LocalForceScale = 0.00f;
    this->m_ChangeWindScale = false;
    this->m_GroupWindScale = 0.00f;
    this->m_ChangeMassScale = false;
    this->m_GroupMassScale = 0.00f;
    this->m_ChangeParkRate = false;
    this->m_GroupParkRateScale = 0.00f;
    this->m_ChangeActorFictitiousForce = false;
    this->m_GroupActorFictitiousForceScale = 0.00f;
    this->m_ChangeActorCentrifugal = false;
    this->m_GroupActorCentrifugalScale = 0.00f;
    this->m_ChangeActorImpulse = false;
    this->m_GroupActorImpulseScale = 0.00f;
    this->m_ChangeActorRotDrag = false;
    this->m_GroupActorRotDragScale = 0.00f;
    this->m_ChangeActorTransDrag = false;
    this->m_GroupActorTransDragScale = 0.00f;
    this->m_ChangeChainRootFictitiousForce = false;
    this->m_GroupChainRootFictitiousForceScale = 0.00f;
    this->m_ChangeChainRootCentrifugal = false;
    this->m_GroupChainRootCentrifugalScale = 0.00f;
    this->m_ChangeChainRootImpulse = false;
    this->m_GroupChainRootImpulseScale = 0.00f;
    this->m_ChangeChainRootRotDrag = false;
    this->m_GroupChainRootRotDragScale = 0.00f;
    this->m_ChangeChainRootTransDrag = false;
    this->m_GroupChainRootTransDragScale = 0.00f;
    this->m_ChangeBodyDrag = false;
    this->m_GroupBodyDragScale = 0.00f;
    this->m_ChangeBodyLift = false;
    this->m_GroupBodyLiftScale = 0.00f;
    this->m_ChangeBodyDamping = false;
    this->m_GroupBodyDampingScale = 0.00f;
    this->m_ChangeBodyConstraintDamping = false;
    this->m_GroupBodyConstraintDampingScale = 0.00f;
    this->m_ChangeBodyVelocityDamping = false;
    this->m_GroupBodyVelocityDampingScale = 0.00f;
    this->m_ChangeBodyRadius = false;
    this->m_GroupBodyRadiusScale = 0.00f;
    this->m_ChangeBodyFriction = false;
    this->m_GroupBodyFrictionScale = 0.00f;
    this->m_ChangeBodyGravity = false;
    this->m_GroupBodyGravityScale = 0.00f;
}


