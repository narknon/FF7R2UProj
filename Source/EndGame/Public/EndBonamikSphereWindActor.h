#pragma once
#include "CoreMinimal.h"
#include "EndBonamikWindActor.h"
#include "EndBonamikSphereWindActor.generated.h"

class UEndBonamikSphereWindComponent;

UCLASS(Blueprintable)
class AEndBonamikSphereWindActor : public AEndBonamikWindActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBonamikSphereWindComponent* WindComponent;
    
public:
    AEndBonamikSphereWindActor(const FObjectInitializer& ObjectInitializer);

};

