#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimTypes.h"
#include "MoveActorDataCache.generated.h"

class AActor;
class USceneComponent;
class USplineComponent;

USTRUCT(BlueprintType)
struct ENDGAME_API FMoveActorDataCache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AActor> OwnerActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAnimNotifyEvent LocalEvent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* SplineComp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USceneComponent* MovingComponent;
    
    FMoveActorDataCache();
};

