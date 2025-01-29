#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "EEndRestrictedAreaVehicleType.h"
#include "EndRestrictedAreaNotifyData.h"
#include "EndRestrictedAreaNotifyDataInterval.h"
#include "EndVehicleRestrictedAreaSplineActor.generated.h"

class UEndVehicleRestrictedAreaSplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndVehicleRestrictedAreaSplineActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndRestrictedAreaVehicleType RestrictedAreaVehicleType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableSpline;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> ValidAreaConditions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableHeightLimit;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval HeightLimitRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HorizontalLimitDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableNotify;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndRestrictedAreaNotifyData DefaultNotifyData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndRestrictedAreaNotifyDataInterval> OverrideNotifyDataList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SendTriggerLimitDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVehicleRestrictedAreaSplineComponent* SplineComponent;
    
public:
    AEndVehicleRestrictedAreaSplineActor(const FObjectInitializer& ObjectInitializer);

};

