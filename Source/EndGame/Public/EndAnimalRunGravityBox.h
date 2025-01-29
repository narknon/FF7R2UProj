#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndAnimalRunGravityBox.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndAnimalRunGravityBox : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndAnimalRunGravityBox(const FObjectInitializer& ObjectInitializer);

};

