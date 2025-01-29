#pragma once
#include "CoreMinimal.h"
#include "NavMesh/NavMeshRenderingComponent.h"
#include "EndNavMeshRenderingComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndNavMeshRenderingComponent : public UNavMeshRenderingComponent {
    GENERATED_BODY()
public:
    UEndNavMeshRenderingComponent(const FObjectInitializer& ObjectInitializer);

};

