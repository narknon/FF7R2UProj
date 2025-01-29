#pragma once
#include "CoreMinimal.h"
#include "EndCinemaAttachParameters.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaAttachParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachSocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachComponentName;
    
    ENDGAME_API FEndCinemaAttachParameters();
};

