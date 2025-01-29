#pragma once
#include "CoreMinimal.h"
#include "eEndBattleDamageSourceHitReactionType_BD.h"
#include "eEndBattleDamageSourceProperty_BD.h"
#include "RagdollActivationTimeOverride.generated.h"

USTRUCT(BlueprintType)
struct FRagdollActivationTimeOverride {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<eEndBattleDamageSourceHitReactionType_BD> ReactionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<eEndBattleDamageSourceProperty_BD> DamageSourceProperty;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ActivationTime;
    
    BODYDRIVERPLUGIN_API FRagdollActivationTimeOverride();
};

