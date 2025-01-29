#pragma once
#include "CoreMinimal.h"
#include "EFriendSpecialAbilityConditionType.h"
#include "EndBattleFriendSpecialAbilityParam.generated.h"

USTRUCT(BlueprintType)
struct FEndBattleFriendSpecialAbilityParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EFriendSpecialAbilityConditionType> ExecuteConditions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Frequency;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Priority;
    
    ENDGAME_API FEndBattleFriendSpecialAbilityParam();
};

