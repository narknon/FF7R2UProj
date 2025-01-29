#pragma once
#include "CoreMinimal.h"
#include "EndObjectBase.h"
#include "EndObjectParty.generated.h"

USTRUCT(BlueprintType)
struct FEndObjectParty : public FEndObjectBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetIconResponseAreaForSelf;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetIconResponseAreaForOthers;
    
    ENDGAME_API FEndObjectParty();
};

