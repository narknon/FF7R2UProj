#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndAdditiveDamage_HitBoneSetting.h"
#include "RigUnit_EndAdditiveDamage_HitSetting.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndAdditiveDamage_HitSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIdle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bWalk;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bRun;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndAdditiveDamage_HitBoneSetting BaseSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndAdditiveDamage_HitBoneSetting> AdditiveSettings;
    
    ENDGAME_API FRigUnit_EndAdditiveDamage_HitSetting();
};

