#pragma once
#include "CoreMinimal.h"
#include "EndBonamikWindActor.h"
#include "EndBonamikBoxWindActor.generated.h"

class UEndBonamikBoxWindComponent;

UCLASS(Blueprintable)
class AEndBonamikBoxWindActor : public AEndBonamikWindActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBonamikBoxWindComponent* WindComponent;
    
public:
    AEndBonamikBoxWindActor(const FObjectInitializer& ObjectInitializer);

};

