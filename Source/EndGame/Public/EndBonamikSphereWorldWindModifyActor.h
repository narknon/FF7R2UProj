#pragma once
#include "CoreMinimal.h"
#include "EndBonamikWorldWindModifyActor.h"
#include "EndBonamikSphereWorldWindModifyActor.generated.h"

class UEndBonamikSphereWorldWindModifyComponent;

UCLASS(Blueprintable)
class AEndBonamikSphereWorldWindModifyActor : public AEndBonamikWorldWindModifyActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBonamikSphereWorldWindModifyComponent* WorldWindModifyComponent;
    
public:
    AEndBonamikSphereWorldWindModifyActor(const FObjectInitializer& ObjectInitializer);

};

