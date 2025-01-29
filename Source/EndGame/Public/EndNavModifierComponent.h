#pragma once
#include "CoreMinimal.h"
#include "NavModifierComponent.h"
#include "EndNavModifierComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndNavModifierComponent : public UNavModifierComponent {
    GENERATED_BODY()
public:
    UEndNavModifierComponent(const FObjectInitializer& ObjectInitializer);

};

