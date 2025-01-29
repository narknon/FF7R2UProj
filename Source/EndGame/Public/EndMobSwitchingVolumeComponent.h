#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndMobSwitchingVolumeComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndMobSwitchingVolumeComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndMobSwitchingVolumeComponent(const FObjectInitializer& ObjectInitializer);

};

