#pragma once
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "SQEXSEADVolumeComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class SQEXSEAD_API USQEXSEADVolumeComponent : public UPrimitiveComponent {
    GENERATED_BODY()
public:
    USQEXSEADVolumeComponent(const FObjectInitializer& ObjectInitializer);

};

