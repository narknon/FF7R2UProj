#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionDamageReciveInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldActionDamageReciveInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName HitTriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> OnlyReciveDamageSourceIdArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> OnlyReciveAttackerActorNameArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActiveControlByStoryFlag;
    
    ENDGAME_API FEndFieldActionDamageReciveInfo();
};

