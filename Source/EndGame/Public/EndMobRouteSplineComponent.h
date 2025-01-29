#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Components/SplineComponent.h"
#include "EndMobRouteSplineCurveDefaults.h"
#include "EndMobRouteSplineComponent.generated.h"

class UEndMobRouteSplineMetadata;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndMobRouteSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndMobRouteSplineCurveDefaults MobRouteSplineDefaults;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndMobRouteSplineCurveDefaults PreviousMobRouteSplineDefaults;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMobRouteSplineMetadata* MobRouteSplineMetadata;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FInterpCurveFloat Width;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FInterpCurveVector OuterEdge;
    
public:
    UEndMobRouteSplineComponent(const FObjectInitializer& ObjectInitializer);

};

