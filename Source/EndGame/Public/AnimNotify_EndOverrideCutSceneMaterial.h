#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EndOverrideCutSceneMaterial.generated.h"

class UMaterialInterface;

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UAnimNotify_EndOverrideCutSceneMaterial : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MaterialSlotName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UMaterialInterface* Material;
    
    UAnimNotify_EndOverrideCutSceneMaterial();

};

