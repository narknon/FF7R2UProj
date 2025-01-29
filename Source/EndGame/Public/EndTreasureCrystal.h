#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentPhysicsStaticMeshActor.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndTreasureCrystal.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndTreasureCrystal : public AEndEnvironmentPhysicsStaticMeshActor, public IEndNaviMapDataProviderInterface {
    GENERATED_BODY()
public:
    AEndTreasureCrystal(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

