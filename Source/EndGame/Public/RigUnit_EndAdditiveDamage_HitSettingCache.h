#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndAdditiveDamage_HitBoneSettingCache.h"
#include "RigUnit_EndAdditiveDamage_HitSettingCache.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndAdditiveDamage_HitSettingCache {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndAdditiveDamage_HitBoneSettingCache BaseSettingCache;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndAdditiveDamage_HitBoneSettingCache> AdditiveSettingCaches;
    
    ENDGAME_API FRigUnit_EndAdditiveDamage_HitSettingCache();
};

