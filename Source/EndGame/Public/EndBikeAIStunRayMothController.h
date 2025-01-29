#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIStunRayController.h"
#include "EndBikeAIStunRayMothController.generated.h"

class AEndBikeAIMothSlasherController;

UCLASS(Blueprintable)
class AEndBikeAIStunRayMothController : public AEndBikeAIStunRayController {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndBikeAIMothSlasherController* mMothSlasherAI;
    
public:
    AEndBikeAIStunRayMothController(const FObjectInitializer& ObjectInitializer);

};

