#include "EndAIMoveDefinitionJumpBase.h"

UEndAIMoveDefinitionJumpBase::UEndAIMoveDefinitionJumpBase() {
    this->bNotActionInterrupt = true;
    this->bNotReactionAction = true;
    this->JumpAngle = 45.00f;
    this->RotationInterpSpeed = 5.00f;
    this->GravityScale = 5.00f;
    this->JumpHeightMax = 0.00f;
    this->JumpTimeMin = 0.00f;
    this->bIgnoreOnlyNavMeshMove = false;
}


