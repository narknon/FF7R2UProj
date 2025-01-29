#pragma once
#include "CoreMinimal.h"
#include "EndItemDropSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndItemDropSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MakoStoneDamageSourceOwnerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableMakoStoneEffect;
    
    ENDGAME_API FEndItemDropSetting();
};

