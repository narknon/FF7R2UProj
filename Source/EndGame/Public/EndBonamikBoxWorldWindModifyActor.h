#pragma once
#include "CoreMinimal.h"
#include "EndBonamikWorldWindModifyActor.h"
#include "EndBonamikBoxWorldWindModifyActor.generated.h"

class UEndBonamikBoxWorldWindModifyComponent;

UCLASS(Blueprintable)
class AEndBonamikBoxWorldWindModifyActor : public AEndBonamikWorldWindModifyActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBonamikBoxWorldWindModifyComponent* WorldWindModifyComponent;
    
public:
    AEndBonamikBoxWorldWindModifyActor(const FObjectInitializer& ObjectInitializer);

};

