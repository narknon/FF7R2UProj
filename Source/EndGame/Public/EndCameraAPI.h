#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EEndCameraLookAtDeactivateType.h"
#include "EEndCameraModuleLayer.h"
#include "EndCameraAPI.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndCameraAPI : public UObject {
    GENERATED_BODY()
public:
    UEndCameraAPI();

    UFUNCTION(BlueprintCallable)
    static void SetOverrideAdjustLengthBattleCamera(FName CharaSpecID, FName CameraModuleID, bool bApplyToLockOnCamera);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideAdjustLengthBattleCamera(FName CharaSpecID);
    
    UFUNCTION(BlueprintCallable)
    static void DeactivateFieldCameraModule(EEndCameraModuleLayer moduleType);
    
    UFUNCTION(BlueprintCallable)
    static void ActivateLookAtCamera(FVector TargetLocation, const FName& DatatableName, bool bEnableInputRotation, EEndCameraLookAtDeactivateType deactivateType, bool bIsTurnBack);
    
};

