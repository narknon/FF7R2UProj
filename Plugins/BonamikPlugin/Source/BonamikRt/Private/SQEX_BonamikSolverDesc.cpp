#include "SQEX_BonamikSolverDesc.h"

FSQEX_BonamikSolverDesc::FSQEX_BonamikSolverDesc() {
    this->m_GroupId = 0;
    this->m_IsEnable = false;
    this->m_EnableGround = false;
    this->mReferenceFrameUpdateMode = 0;
    this->m_RefUpVec = 0;
    this->mIsCollisionResampleCapsule = 0;
    this->mCollisionResampleCapsuleStep = 0.00f;
    this->mCollisionBalance = 0.00f;
    this->mWindScale = 0.00f;
    this->mLocalForceScale = 0.00f;
    this->mParkRateScale = 0.00f;
    this->mActorFictitiousForceScale = 0.00f;
    this->mActorCentrifugalScale = 0.00f;
    this->mActorImpulseScale = 0.00f;
    this->mActorRotDragScale = 0.00f;
    this->mActorTransDragScale = 0.00f;
    this->mChainRootFictitiousForceScale = 0.00f;
    this->mChainRootCentrifugalScale = 0.00f;
    this->mChainRootImpulseScale = 0.00f;
    this->mChainRootRotDragScale = 0.00f;
    this->mChainRootTransDragScale = 0.00f;
    this->mBodyDragScale = 0.00f;
    this->mBodyLiftScale = 0.00f;
    this->m_IsUseConeSEQ = false;
    this->m_IsEnableDraw = false;
    this->m_ColIter = 0;
    this->m_ConsIter = 0;
    this->m_ConeIter = 0;
    this->m_LinkIter = 0;
    this->m_SolverIter = 0;
    this->m_TagId = 0;
    this->m_CollisionTagId = 0;
    this->m_UseAccurateGroundTest = false;
    this->m_LODdistance = 0.00f;
}

