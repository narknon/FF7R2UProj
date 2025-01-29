#pragma once
#include "CoreMinimal.h"
#include "EEndCameraModuleLayer.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsFieldCameraModule.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsFieldCameraModule : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndCameraModuleLayer> m_CameraModuleLayers;
    
    UEndBTDecorator_IsFieldCameraModule();

};

