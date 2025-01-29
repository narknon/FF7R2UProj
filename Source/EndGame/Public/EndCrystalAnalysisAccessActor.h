#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "EndActorInterface.h"
#include "EndCrystalAnalysisAccessActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndCrystalAnalysisAccessActor : public AActor, public IEndActorInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector TargetPointOffset;
    
    AEndCrystalAnalysisAccessActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

