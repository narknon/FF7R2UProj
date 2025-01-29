#pragma once
#include "CoreMinimal.h"
#include "EndCylinderComponent.h"
#include "EndFieldActionChocoboUpdraftCylinderComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldActionChocoboUpdraftCylinderComponent : public UEndCylinderComponent {
    GENERATED_BODY()
public:
    UEndFieldActionChocoboUpdraftCylinderComponent(const FObjectInitializer& ObjectInitializer);

};

