#pragma once
#include "CoreMinimal.h"
#include "EndBonamikWindActor.h"
#include "EndBonamikCapsuleWindActor.generated.h"

class UEndBonamikCapsuleWindComponent;

UCLASS(Blueprintable)
class AEndBonamikCapsuleWindActor : public AEndBonamikWindActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBonamikCapsuleWindComponent* WindComponent;
    
public:
    AEndBonamikCapsuleWindActor(const FObjectInitializer& ObjectInitializer);

};

