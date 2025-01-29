#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndSwitchAreaBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndSwitchAreaBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndSwitchAreaBoxComponent(const FObjectInitializer& ObjectInitializer);

};

