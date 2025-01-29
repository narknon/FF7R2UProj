#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndPixelCoordinateAnimationUserData.generated.h"

class UEndPixelCoordinateAnimationSettings;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndPixelCoordinateAnimationUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndPixelCoordinateAnimationSettings* PixelCoordinateAnimationSettings;
    
    UEndPixelCoordinateAnimationUserData();

};

