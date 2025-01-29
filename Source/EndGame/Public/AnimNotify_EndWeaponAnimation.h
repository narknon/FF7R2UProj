#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EWeaponSlot.h"
#include "AnimNotify_EndWeaponAnimation.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndWeaponAnimation : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot Slot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AnimationName;
    
    UAnimNotify_EndWeaponAnimation();

};

