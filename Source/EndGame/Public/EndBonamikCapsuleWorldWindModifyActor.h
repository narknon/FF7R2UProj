#pragma once
#include "CoreMinimal.h"
#include "EndBonamikWorldWindModifyActor.h"
#include "EndBonamikCapsuleWorldWindModifyActor.generated.h"

class UEndBonamikCapsuleWorldWindModifyComponent;

UCLASS(Blueprintable)
class AEndBonamikCapsuleWorldWindModifyActor : public AEndBonamikWorldWindModifyActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBonamikCapsuleWorldWindModifyComponent* WorldWindModifyComponent;
    
public:
    AEndBonamikCapsuleWorldWindModifyActor(const FObjectInitializer& ObjectInitializer);

};

