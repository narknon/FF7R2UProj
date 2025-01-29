#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndDeformAnimationSettings.h"
#include "EndDeformAnimationUserData.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndDeformAnimationUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndDeformAnimationSettings DeformAnimationSettings;
    
    UEndDeformAnimationUserData();

};

