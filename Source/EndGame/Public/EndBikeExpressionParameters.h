#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndBikeExpressionMufflerParameters.h"
#include "EndBikeExpressionSteeringParameters.h"
#include "EndBikeExpressionSuspensionParameters.h"
#include "EndBikeExpressionWheelAxleParameters.h"
#include "EndBikeExpressionWheelSpinParameters.h"
#include "EndBikeExpressionWindParameters.h"
#include "EndBikeExpressionParameters.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndBikeExpressionParameters : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeExpressionWheelSpinParameters> WheelSpinSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeExpressionMufflerParameters> MufflerSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeExpressionSteeringParameters SteeringSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeExpressionWheelAxleParameters> WheelAxleSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeExpressionSuspensionParameters> SuspensionSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeExpressionWindParameters WindSetting;
    
    UEndBikeExpressionParameters();

};

