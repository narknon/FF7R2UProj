#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndFieldActionChocoboClimbOverlapBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndFieldActionChocoboClimbOverlapBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndFieldActionChocoboClimbOverlapBoxComponent(const FObjectInitializer& ObjectInitializer);

};

