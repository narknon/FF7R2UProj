#pragma once
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "EndNavMeshAssetComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndNavMeshAssetComponent : public UPrimitiveComponent {
    GENERATED_BODY()
public:
    UEndNavMeshAssetComponent(const FObjectInitializer& ObjectInitializer);

};

