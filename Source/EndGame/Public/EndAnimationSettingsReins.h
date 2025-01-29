#pragma once
#include "CoreMinimal.h"
#include "EndAnimationSettingsReins.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationSettingsReins {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SettingName;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetSocketName;
    
    ENDGAME_API FEndAnimationSettingsReins();
};

