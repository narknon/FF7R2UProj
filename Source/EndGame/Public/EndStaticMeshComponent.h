#pragma once
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "EndStaticMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndStaticMeshComponent : public UStaticMeshComponent {
    GENERATED_BODY()
public:
    UEndStaticMeshComponent(const FObjectInitializer& ObjectInitializer);

};

