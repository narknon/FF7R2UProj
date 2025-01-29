#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EWeaponSlot.h"
#include "AnimNotify_EndWeaponDrop.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndWeaponDrop : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EWeaponSlot> Slots;
    
    UAnimNotify_EndWeaponDrop();

};

