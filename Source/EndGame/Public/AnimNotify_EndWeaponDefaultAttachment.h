#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAnimBehaviorMode.h"
#include "EWeaponSlot.h"
#include "AnimNotify_EndWeaponDefaultAttachment.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndWeaponDefaultAttachment : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot Slot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimBehaviorMode BehaviorMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SocketName;
    
    UAnimNotify_EndWeaponDefaultAttachment();

};

