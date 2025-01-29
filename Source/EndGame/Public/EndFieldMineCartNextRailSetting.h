#pragma once
#include "CoreMinimal.h"
#include "EndFieldMineCartNextRailSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldMineCartNextRailSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetRailName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bReverseTarget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SwitchStoryFlag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DisableStoryFlag;
    
    ENDGAME_API FEndFieldMineCartNextRailSetting();
};

