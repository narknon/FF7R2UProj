#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndAdditiveDamage_HitSetting.h"
#include "RigUnit_EndAdditiveDamage_Settings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndAdditiveDamage_Settings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndAdditiveDamage_HitSetting> HitSettings;
    
    ENDGAME_API FRigUnit_EndAdditiveDamage_Settings();
};

