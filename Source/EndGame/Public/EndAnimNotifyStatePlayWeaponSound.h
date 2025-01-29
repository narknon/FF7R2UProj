#pragma once
#include "CoreMinimal.h"
#include "EWeaponSlot.h"
#include "EndAnimNotifyStatePlaySound.h"
#include "EndAnimNotifyStatePlayWeaponSound.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyStatePlayWeaponSound : public UEndAnimNotifyStatePlaySound {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot WeaponSlot;
    
    UEndAnimNotifyStatePlayWeaponSound();

};

