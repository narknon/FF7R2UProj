#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndWallIgnoreBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndWallIgnoreBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndWallIgnoreBoxComponent(const FObjectInitializer& ObjectInitializer);

};

