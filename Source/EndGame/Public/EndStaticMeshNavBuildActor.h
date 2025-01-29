#pragma once
#include "CoreMinimal.h"
#include "EndEnvProxyActor.h"
#include "EndStaticMeshNavBuildActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndStaticMeshNavBuildActor : public AEndEnvProxyActor {
    GENERATED_BODY()
public:
    AEndStaticMeshNavBuildActor(const FObjectInitializer& ObjectInitializer);

};

