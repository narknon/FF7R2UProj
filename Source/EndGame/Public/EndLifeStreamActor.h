#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndGatherableLife.h"
#include "EndLifeStreamActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndLifeStreamActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndGatherableLife m_Worker;
    
    AEndLifeStreamActor(const FObjectInitializer& ObjectInitializer);

};

