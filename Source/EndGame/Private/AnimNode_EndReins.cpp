#include "AnimNode_EndReins.h"

FAnimNode_EndReins::FAnimNode_EndReins() {
    this->ClusterSize = 0.00f;
    this->WorldSize = 0.00f;
    this->ReserveConstraintClusterCount = 0;
    this->PositionIterationCount = 0;
    this->VelocityIterationCount = 0;
    this->ConstantVelocityDumping = 0.00f;
    this->ConstantAngularVelocityDumping = 0.00f;
    this->HitCollisionVelocityRestitutionDumping = 0.00f;
    this->HitCollisionVelocityFrictionDumping = 0.00f;
    this->VelocityInterpRate = 0.00f;
    this->RopeLength = 0.00f;
    this->RopeThicknessScale = 0.00f;
    this->ParticleCount = 0;
    this->ParticleRadius = 0.00f;
    this->SimulationStiffness = 0.00f;
    this->BendingConstraintStiffness = 0.00f;
    this->BendingConstraintRelayPointStiffness = 0.00f;
    this->RestitutionCoeff = 0.00f;
    this->FrictionCoeff = 0.00f;
}

