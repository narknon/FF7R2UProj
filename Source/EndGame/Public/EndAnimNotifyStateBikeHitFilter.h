#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EEndBikeAbilityDistanceType.h"
#include "EEndBikeHitFilterPartsType.h"
#include "EndAnimNotifyStateBikeHitFilter.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyStateBikeHitFilter : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBikeHitFilterPartsType PartsType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSet<EEndBikeAbilityDistanceType> PassAbilityDistanceTypes;
    
    UEndAnimNotifyStateBikeHitFilter();

};

