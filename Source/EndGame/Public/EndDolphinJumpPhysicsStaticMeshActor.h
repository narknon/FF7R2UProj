#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentPhysicsStaticMeshActor.h"
#include "EndDolphinJumpPhysicsStaticMeshActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndDolphinJumpPhysicsStaticMeshActor : public AEndEnvironmentPhysicsStaticMeshActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnableTarget;
    
public:
    AEndDolphinJumpPhysicsStaticMeshActor(const FObjectInitializer& ObjectInitializer);

};

