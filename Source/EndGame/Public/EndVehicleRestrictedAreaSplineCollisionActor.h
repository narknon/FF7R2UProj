#pragma once
#include "CoreMinimal.h"
#include "EndVehicleRestrictedAreaSplineActor.h"
#include "EndVehicleRestrictedAreaSplineCollisionActor.generated.h"

class UEndVehicleRestrictedAreaWallCollisionComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndVehicleRestrictedAreaSplineCollisionActor : public AEndVehicleRestrictedAreaSplineActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVehicleRestrictedAreaWallCollisionComponent* WallCollisionComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseAsCollisionWallOnly;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseSplineCurveAuto;
    
public:
    AEndVehicleRestrictedAreaSplineCollisionActor(const FObjectInitializer& ObjectInitializer);

};

