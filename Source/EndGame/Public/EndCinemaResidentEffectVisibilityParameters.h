#pragma once
#include "CoreMinimal.h"
#include "EEndCinemaResidentEffectVisibility.h"
#include "EndCinemaResidentEffectVisibilityParameters.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaResidentEffectVisibilityParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetLocationName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetAccessorID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCinemaResidentEffectVisibility Visibility;
    
    ENDGAME_API FEndCinemaResidentEffectVisibilityParameters();
};

