#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentSkeletalMeshActor.h"
#include "EndEnvironmentClothSkeletalMeshActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndEnvironmentClothSkeletalMeshActor : public AEndEnvironmentSkeletalMeshActor {
    GENERATED_BODY()
public:
    AEndEnvironmentClothSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

};

