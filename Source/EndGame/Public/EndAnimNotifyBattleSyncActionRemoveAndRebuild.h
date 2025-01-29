#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleSyncActionRemoveAndRebuild.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleSyncActionRemoveAndRebuild : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RebuildSyncActionID;
    
    UEndAnimNotifyBattleSyncActionRemoveAndRebuild();

};

