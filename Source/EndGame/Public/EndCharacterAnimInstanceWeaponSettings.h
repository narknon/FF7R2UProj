#pragma once
#include "CoreMinimal.h"
#include "EWeaponSlot.h"
#include "EndCharacterAnimInstanceWeaponSettings.generated.h"

USTRUCT(BlueprintType)
struct FEndCharacterAnimInstanceWeaponSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot Slot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachSocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bVisibility;
    
    ENDGAME_API FEndCharacterAnimInstanceWeaponSettings();
};

