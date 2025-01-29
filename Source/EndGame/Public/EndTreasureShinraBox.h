#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentPhysicsStaticMeshActor.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndTreasureShinraBox.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndTreasureShinraBox : public AEndEnvironmentPhysicsStaticMeshActor, public IEndNaviMapDataProviderInterface {
    GENERATED_BODY()
public:
    AEndTreasureShinraBox(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

