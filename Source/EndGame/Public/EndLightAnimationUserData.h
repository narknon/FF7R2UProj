#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndLightAnimationUserData.generated.h"

class UEndLightAnimationSettings;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndLightAnimationUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndLightAnimationSettings* LightAnimationSettings;
    
    UEndLightAnimationUserData();

};

