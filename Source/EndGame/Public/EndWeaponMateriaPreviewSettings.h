#pragma once
#include "CoreMinimal.h"
#include "EMateriaType.h"
#include "EndWeaponMateriaPreviewSettings.generated.h"

USTRUCT(BlueprintType)
struct FEndWeaponMateriaPreviewSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Slot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EMateriaType MateriaType;
    
    ENDGAME_API FEndWeaponMateriaPreviewSettings();
};

