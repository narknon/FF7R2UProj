#pragma once
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "EndDebugTextComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndDebugTextComponent : public UPrimitiveComponent {
    GENERATED_BODY()
public:
    UEndDebugTextComponent(const FObjectInitializer& ObjectInitializer);

};

