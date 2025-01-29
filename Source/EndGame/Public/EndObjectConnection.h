#pragma once
#include "CoreMinimal.h"
#include "EndObjectConnection.generated.h"

USTRUCT(BlueprintType)
struct FEndObjectConnection {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 OwnerNodeGUID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OwnerPinName;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 TargetNodeGUID;
    
    ENDGAME_API FEndObjectConnection();
};

