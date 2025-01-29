#pragma once
#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "SQEXSEADAudioComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class SQEXSEAD_API USQEXSEADAudioComponent : public UAudioComponent {
    GENERATED_BODY()
public:
    USQEXSEADAudioComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    float GetPlaybackTimePercent();
    
};

