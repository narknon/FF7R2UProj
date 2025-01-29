#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActor.h"
#include "EndDolphinJumpItemActor.generated.h"

class UEndDolphinJumpOceanFloaterComponent;

UCLASS(Blueprintable)
class AEndDolphinJumpItemActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ItemParameterID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndDolphinJumpOceanFloaterComponent* OceanFloaterComponent;
    
public:
    AEndDolphinJumpItemActor(const FObjectInitializer& ObjectInitializer);

};

