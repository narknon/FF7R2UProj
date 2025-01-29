#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAnimNotifyMiniGameBuggyEnergyType.h"
#include "EndAnimNotifyMiniGameBuggyEnergy.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyMiniGameBuggyEnergy : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyMiniGameBuggyEnergyType Type;
    
    UEndAnimNotifyMiniGameBuggyEnergy();

};

