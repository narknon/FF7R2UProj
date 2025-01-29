#pragma once
#include "CoreMinimal.h"
#include "EndFieldHookRopeSwingToMoveTarget.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FEndFieldHookRopeSwingToMoveTarget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AActor* TargetActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EndAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotSpeedRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotFriction;
    
    ENDGAME_API FEndFieldHookRopeSwingToMoveTarget();
};

