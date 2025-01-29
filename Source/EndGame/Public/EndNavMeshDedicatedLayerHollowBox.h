#pragma once
#include "CoreMinimal.h"
#include "NavPriorRegistInfo.h"
#include "NavModifierVolume.h"
#include "EndNavMeshDedicatedLayerHollowBox.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNavMeshDedicatedLayerHollowBox : public ANavModifierVolume {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNavPriorRegistInfo NavPriorInfo;
    
public:
    AEndNavMeshDedicatedLayerHollowBox(const FObjectInitializer& ObjectInitializer);

};

