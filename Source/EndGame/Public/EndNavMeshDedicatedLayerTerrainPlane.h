#pragma once
#include "CoreMinimal.h"
#include "NavPriorRegistInfo.h"
#include "NavModifierVolume.h"
#include "EndNavMeshDedicatedLayerTerrainPlane.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNavMeshDedicatedLayerTerrainPlane : public ANavModifierVolume {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNavPriorRegistInfo NavPriorInfo;
    
public:
    AEndNavMeshDedicatedLayerTerrainPlane(const FObjectInitializer& ObjectInitializer);

};

