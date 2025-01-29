#pragma once
#include "CoreMinimal.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "GameFramework/PhysicsVolume.h"
#include "EEndWaterType.h"
#include "EWaterNavBuildType.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndWaterVolumeInterface.h"
#include "Templates/SubclassOf.h"
#include "EndWaterVolume.generated.h"

class UNavArea;

UCLASS(Blueprintable)
class ENDGAME_API AEndWaterVolume : public APhysicsVolume, public IEndWaterVolumeInterface, public INavRelevantInterface, public IEndNaviMapDataProviderInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndWaterType WaterType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWaterNavBuildType BuildType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UNavArea> AreaClass;
    
public:
    AEndWaterVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

