#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndChocoboJetOneWayGuideOverlapBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndChocoboJetOneWayGuideOverlapBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndChocoboJetOneWayGuideOverlapBoxComponent(const FObjectInitializer& ObjectInitializer);

};

