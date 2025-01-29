#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndAIRecognitionBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndAIRecognitionBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndAIRecognitionBoxComponent(const FObjectInitializer& ObjectInitializer);

};

