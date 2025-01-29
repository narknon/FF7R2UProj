#pragma once
#include "CoreMinimal.h"
#include "EWeaponSlot.h"
#include "EndAnimNotifyPlaySound.h"
#include "EndAnimNotifyPlayWeaponSound.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyPlayWeaponSound : public UEndAnimNotifyPlaySound {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot WeaponSlot;
    
    UEndAnimNotifyPlayWeaponSound();

};

