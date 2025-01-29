#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndNotifyBattleCameraChangeTimingType.h"
#include "EndAnimNotifyBattleCameraChangeTiming.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleCameraChangeTiming : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNotifyBattleCameraChangeTimingType ChangeTimingType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ReplaceOwnerActorName;
    
    UEndAnimNotifyBattleCameraChangeTiming();

};

