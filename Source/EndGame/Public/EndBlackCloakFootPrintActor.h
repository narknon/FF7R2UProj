#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndBlackCloakFootPrintActor.generated.h"

class UBlueprint;

UCLASS(Blueprintable)
class ENDGAME_API AEndBlackCloakFootPrintActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBlueprint* BPInfo;
    
    AEndBlackCloakFootPrintActor(const FObjectInitializer& ObjectInitializer);

};

