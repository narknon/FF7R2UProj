#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshComponent.h"
#include "EndWheeledVehicleSkeletalMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndWheeledVehicleSkeletalMeshComponent : public UEndSkeletalMeshComponent {
    GENERATED_BODY()
public:
    UEndWheeledVehicleSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer);

};

