#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndNormalizedCoordinateAnimationUserData.generated.h"

class UEndNormalizedCoordinateAnimationSettings;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndNormalizedCoordinateAnimationUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndNormalizedCoordinateAnimationSettings* NormalizedCoordinateAnimationSettings;
    
    UEndNormalizedCoordinateAnimationUserData();

};

