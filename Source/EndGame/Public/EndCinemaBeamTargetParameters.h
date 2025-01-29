#pragma once
#include "CoreMinimal.h"
#include "EndCinemaBeamTargetParameters.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaBeamTargetParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetSocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetComponentName;
    
    ENDGAME_API FEndCinemaBeamTargetParameters();
};

