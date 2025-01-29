#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldActionWallRunningActor.generated.h"

class UEndFieldActionTriggerComponent;
class UEndFieldAddWallRunningTriggerBoxMaker;
class USplineComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionWallRunningActor : public AEndFieldActionSaveActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* WallRunningVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bWallRunningVolume_BlockBoxOutMove;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bWallRunningVolume_SetJumpDownPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector WallRunningVolume_JumpDownPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndFieldAddWallRunningTriggerBoxMaker*> AddWallRunningVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDebugViewBoxs;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* RailCameraSplineComponent;
    
public:
    AEndFieldActionWallRunningActor(const FObjectInitializer& ObjectInitializer);

};

