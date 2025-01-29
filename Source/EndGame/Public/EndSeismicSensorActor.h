#pragma once
#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "EndSkeletalMeshActor.h"
#include "EndSeismicSensorActor.generated.h"

class UObject;
class USoundConcurrency;

UCLASS(Blueprintable)
class ENDGAME_API AEndSeismicSensorActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRuntimeFloatCurve _SEPeriod;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRuntimeFloatCurve _EffectPeriod;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRuntimeFloatCurve _NegativeEffectPeriod;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundConcurrency* _ConcurrencyAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UObject* PositiveSE;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UObject* NegativeSE;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UObject* BeepSE;
    
    AEndSeismicSensorActor(const FObjectInitializer& ObjectInitializer);

};

