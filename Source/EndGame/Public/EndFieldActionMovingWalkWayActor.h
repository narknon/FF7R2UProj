#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionCommonActorBase.h"
#include "EndFieldActionMovingWalkWayActor.generated.h"

class ASkeletalMeshActor;
class AStaticMeshActor;
class UEndFieldActionTriggerComponent;
class UEndFieldMovingWalkwaySplineComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionMovingWalkWayActor : public AEndFieldActionCommonActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TikableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<ASkeletalMeshActor*> WalkwaySkeletalMeshActors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AStaticMeshActor*> WalkwayStaticMeshActors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<ASkeletalMeshActor*> ReverseWalkwaySkeletalMeshActors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AStaticMeshActor*> ReverseWalkwayStaticMeshActors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldMovingWalkwaySplineComponent* MovingPath;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTransform> GuidEffectTransforms;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableWalkwayLimitMove;
    
public:
    AEndFieldActionMovingWalkWayActor(const FObjectInitializer& ObjectInitializer);

};

