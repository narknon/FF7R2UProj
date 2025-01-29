#pragma once
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "EndStaticMeshPhysicsPartsComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndStaticMeshPhysicsPartsComponent : public UStaticMeshComponent {
    GENERATED_BODY()
public:
    UEndStaticMeshPhysicsPartsComponent(const FObjectInitializer& ObjectInitializer);

};

