#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EEndDeactiveResidentEffectType.h"
#include "EndAnimNotifyDeactiveResidentEffect.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyDeactiveResidentEffect : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndDeactiveResidentEffectType DeactiveType;
    
    UEndAnimNotifyDeactiveResidentEffect();

};

