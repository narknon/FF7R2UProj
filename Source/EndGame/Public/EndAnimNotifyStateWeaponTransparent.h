#pragma once
#include "CoreMinimal.h"
#include "EWeaponSlot.h"
#include "EndAnimNotifyStateTransparent.h"
#include "EndAnimNotifyStateWeaponTransparent.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyStateWeaponTransparent : public UEndAnimNotifyStateTransparent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot WeaponSlot;
    
    UEndAnimNotifyStateWeaponTransparent();

};

