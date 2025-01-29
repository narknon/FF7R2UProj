#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BlackCloakFootprintEffectType.h"
#include "BlackCloakFootprintEffectInfo.generated.h"

USTRUCT(BlueprintType)
struct FBlackCloakFootprintEffectInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    BlackCloakFootprintEffectType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform Trans;
    
    ENDGAME_API FBlackCloakFootprintEffectInfo();
};

