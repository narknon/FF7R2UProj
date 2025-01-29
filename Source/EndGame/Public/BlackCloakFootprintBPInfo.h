#pragma once
#include "CoreMinimal.h"
#include "BlackCloakFootprintBPInfo.generated.h"

class UBlueprint;

USTRUCT(BlueprintType)
struct FBlackCloakFootprintBPInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBlueprint* BPInfo;
    
    ENDGAME_API FBlackCloakFootprintBPInfo();
};

