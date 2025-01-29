#pragma once
#include "CoreMinimal.h"
#include "StateObjectHandle.generated.h"

USTRUCT(BlueprintType)
struct FStateObjectHandle {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int64 Guid;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int64 OwnerGUID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StateName;
    
    ENDGAME_API FStateObjectHandle();
};
FORCEINLINE uint32 GetTypeHash(const FStateObjectHandle) { return 0; }

