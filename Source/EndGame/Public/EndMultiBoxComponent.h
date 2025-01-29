#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndMultiBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndMultiBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndMultiBoxComponent(const FObjectInitializer& ObjectInitializer);

};

