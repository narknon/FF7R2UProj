#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADAudioComponent.h"
#include "SQEXSEADLayoutAudioComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, MinimalAPI, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class USQEXSEADLayoutAudioComponent : public USQEXSEADAudioComponent {
    GENERATED_BODY()
public:
    USQEXSEADLayoutAudioComponent(const FObjectInitializer& ObjectInitializer);

};

