#pragma once
#include "CoreMinimal.h"
#include "EEndWaterType.h"
#include "EWaterNavBuildType.h"
#include "EndEnvironmentStaticMeshActor.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndWaterVolumeInterface.h"
#include "EndWaterStaticMeshVolume.generated.h"

class UEndWaterFlowSplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndWaterStaticMeshVolume : public AEndEnvironmentStaticMeshActor, public IEndWaterVolumeInterface, public IEndNaviMapDataProviderInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndWaterType WaterType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndWaterFlowSplineComponent*> WaterFlowComponents;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWaterNavBuildType BuildType;
    
public:
    AEndWaterStaticMeshVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

