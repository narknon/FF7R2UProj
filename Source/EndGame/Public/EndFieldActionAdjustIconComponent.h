#pragma once
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "EndFieldActionAdjustIconComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldActionAdjustIconComponent : public UStaticMeshComponent {
    GENERATED_BODY()
public:
    UEndFieldActionAdjustIconComponent(const FObjectInitializer& ObjectInitializer);

};

