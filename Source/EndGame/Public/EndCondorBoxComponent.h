#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndCondorBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndCondorBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndCondorBoxComponent(const FObjectInitializer& ObjectInitializer);

};

