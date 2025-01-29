#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAnimBehaviorMode.h"
#include "EWeaponSlot.h"
#include "AnimNotify_EndWeaponDefaultVisibility.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndWeaponDefaultVisibility : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot Slot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimBehaviorMode BehaviorMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bVisible;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bReleaseCharaSpecHidden;
    
    UAnimNotify_EndWeaponDefaultVisibility();

};

