#pragma once
#include "CoreMinimal.h"
#include "EndAssignStateChange.generated.h"

USTRUCT(BlueprintType)
struct FEndAssignStateChange {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 OwnerNodeGUID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FName> NextStateChangeID;
    
    ENDGAME_API FEndAssignStateChange();
};

