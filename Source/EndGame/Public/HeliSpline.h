#pragma once
#include "CoreMinimal.h"
#include "HeliSpline.generated.h"

class ULevelSequence;
class USplineComponent;

USTRUCT(BlueprintType)
struct FHeliSpline {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StateChange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StateTrigger;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<USplineComponent*> SplineMoveComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ULevelSequence* SplineMoveComponentSequencer;
    
    ENDGAME_API FHeliSpline();
};

