#include "SQEXSEADAutoSeComponent.h"

USQEXSEADAutoSeComponent::USQEXSEADAutoSeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bAutoActivate = true;
    this->AutoSeCallback = NULL;
    this->SettingData = NULL;
    this->AssetTable = NULL;
    this->DetectionSetting = NULL;
    this->ProcLodSetting = NULL;
    this->CachedMeshReference = NULL;
    this->CachedMovementComponent = NULL;
}


