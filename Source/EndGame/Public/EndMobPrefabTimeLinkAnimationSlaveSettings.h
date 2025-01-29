#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabTimeLinkAnimationSlaveSettings.generated.h"

USTRUCT(BlueprintType)
struct FEndMobPrefabTimeLinkAnimationSlaveSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MobId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Motion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ReplaceBaseMotion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ReplaceBaseLookAtTarget;
    
    ENDGAME_API FEndMobPrefabTimeLinkAnimationSlaveSettings();
};

