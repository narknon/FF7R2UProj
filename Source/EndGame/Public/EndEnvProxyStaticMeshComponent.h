#pragma once
#include "CoreMinimal.h"
#include "EndStaticMeshComponent.h"
#include "EndEnvProxyStaticMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndEnvProxyStaticMeshComponent : public UEndStaticMeshComponent {
    GENERATED_BODY()
public:
    UEndEnvProxyStaticMeshComponent(const FObjectInitializer& ObjectInitializer);

};

