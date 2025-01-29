#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSpecialStatusChangeType.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleSetSpecialStatusChangeState.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleSetSpecialStatusChangeState : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleSpecialStatusChangeType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName stateChangeID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> Params;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ParamIDs;
    
    UEndAnimNotifyBattleSetSpecialStatusChangeState();

};

