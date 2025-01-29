#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EndFieldForceParkourComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldForceParkourComponent : public USceneComponent {
    GENERATED_BODY()
public:
    UEndFieldForceParkourComponent(const FObjectInitializer& ObjectInitializer);

};

