#pragma once
#include "CoreMinimal.h"
#include "EndObjectKnot.generated.h"

USTRUCT(BlueprintType)
struct FEndObjectKnot {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 UniqueIndex;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 OwnerUniqueIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StateName;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 InputPinGUID;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 OutputPinGUID;
    
    ENDGAME_API FEndObjectKnot();
};

