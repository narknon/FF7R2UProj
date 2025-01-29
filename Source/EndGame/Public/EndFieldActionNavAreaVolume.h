#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndFieldActionNavAreaVolume.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldActionNavAreaVolume : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndFieldActionNavAreaVolume(const FObjectInitializer& ObjectInitializer);

};

