#include "SQEX_BonamikBodyDesc.h"

FSQEX_BonamikBodyDesc::FSQEX_BonamikBodyDesc() {
    this->m_GroupId = 0;
    this->m_ColId[0] = 0;
    this->m_ColId[1] = 0;
    this->m_ColId[2] = 0;
    this->m_ColId[3] = 0;
    this->m_ColId[4] = 0;
    this->m_ColId[5] = 0;
    this->m_ColId[6] = 0;
    this->m_ColId[7] = 0;
    this->m_IsKinematic = false;
    this->m_IsCollision = false;
    this->m_Damping = 0.00f;
    this->mVelocityDamping = 0.00f;
    this->mConstraintDamping = 0.00f;
    this->m_Bounciness = 0.00f;
    this->m_Friction = 0.00f;
    this->mGroundAttach = 0.00f;
    this->m_Mass = 0.00f;
    this->mGravityScale = 0.00f;
    this->m_ColShape = ESQEX_Bonamik_CollisionShape_None;
    this->m_Radius = 0.00f;
    this->m_ConcaveRatio = 0.00f;
    this->m_WindDrag = 0.00f;
    this->m_WindLift = 0.00f;
    this->m_LFcoeff = 0.00f;
    this->mLFRootRotWeight = 0.00f;
    this->m_ParkRate = 0.00f;
    this->m_MaxLF = 0.00f;
    this->m_LFdrag = 0.00f;
    this->m_LFlift = 0.00f;
    this->mActorFictitiousForce = 0.00f;
    this->mActorCentrifugal = 0.00f;
    this->mActorImpulse = 0.00f;
    this->mActorRotDrag = 0.00f;
    this->mActorTransDrag = 0.00f;
    this->mChainRootFictitiousForce = 0.00f;
    this->mChainRootCentrifugal = 0.00f;
    this->mChainRootImpulse = 0.00f;
    this->mChainRootRotDrag = 0.00f;
    this->mChainRootTransDrag = 0.00f;
    this->mBodyDrag = 0.00f;
    this->mBodyLift = 0.00f;
    this->m_Index = 0;
    this->m_ParentId = 0;
    this->m_ChildId = 0;
    this->m_IsMultipleCollisionObject = false;
    this->m_Inertia = 0.00f;
    this->m_LocalTransCoeff = 0.00f;
    this->m_MaxLocalTrans = 0.00f;
    this->m_AddiConstType = ESQEX_Bonamik_ConstraintType_None;
    this->m_AddiConstStr = 0.00f;
    this->m_AddiConstRad = 0.00f;
    this->m_CollisionBatchNo = 0;
}

