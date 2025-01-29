#include "SQEX_Bonamik_Component_v2.h"

UDEPRECATED_SQEX_Bonamik_Component_v2::UDEPRECATED_SQEX_Bonamik_Component_v2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bHasSkeletalMeshSkippedTransforms = false;
    this->m_BonamikAsset = NULL;
    this->SkeletalMeshComponent = NULL;
    this->CharacterMovementComponent = NULL;
    this->m_BonamikEnable = false;
    this->m_BonamikAutoDisable = false;
    this->bAccurateBoundsUpdate = false;
    this->PreRollStepOnResume = 0;
    this->PrevScreenSize = 100000002004087734272.00f;
}


