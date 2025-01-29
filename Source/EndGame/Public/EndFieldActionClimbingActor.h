#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldClimbingPointActorInterface.h"
#include "EndFieldActionClimbingActor.generated.h"

class UEndFieldActionTriggerComponent;
class UEndFieldClimbingPointSettingBase;
class USplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionClimbingActor : public AEndFieldActionSaveActorBase, public IEndFieldClimbingPointActorInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* UpperVolume;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int16 RegulationClearVersion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndFieldClimbingPointSettingBase*> ClimbingPointArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTransform> EnterIcons;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AttachPointTargetActorNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bFallStartIsForceCatch;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EnableUseNPCStoryFlag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* RailCameraSplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAutoUpdateRailCameraSplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSetRailCameraSplineComponentToLinear;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float RailCameraProgressSpeed;
    
public:
    AEndFieldActionClimbingActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

