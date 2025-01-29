#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldClimbingJumpPointSetting.h"
#include "EndFieldClimbingPointSettingBase.h"
#include "EndFieldClimbingCatchPointSetting.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldClimbingCatchPointSetting : public UEndFieldClimbingPointSettingBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform LocalLocator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldClimbingJumpPointSetting> JumpPoints;
    
    UEndFieldClimbingCatchPointSetting(const FObjectInitializer& ObjectInitializer);

};

