#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIControllerEnemyBase.h"
#include "EndBikeAIStunRayController.generated.h"

UCLASS(Blueprintable)
class AEndBikeAIStunRayController : public AEndBikeAIControllerEnemyBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AvoidJumpPointDistance;
    
public:
    AEndBikeAIStunRayController(const FObjectInitializer& ObjectInitializer);

};

