#pragma once
#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "EndFieldDebugArrowComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldDebugArrowComponent : public UArrowComponent {
    GENERATED_BODY()
public:
    UEndFieldDebugArrowComponent(const FObjectInitializer& ObjectInitializer);

};

