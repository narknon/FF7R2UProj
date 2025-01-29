#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndSpiderWallMoveAreaBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndSpiderWallMoveAreaBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndSpiderWallMoveAreaBoxComponent(const FObjectInitializer& ObjectInitializer);

};

