#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndWireReelModifierType.h"
#include "AnimNotify_EndModifyWireReel.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndModifyWireReel : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndWireReelModifierType ModifierType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Param01;
    
    UAnimNotify_EndModifyWireReel();

};

