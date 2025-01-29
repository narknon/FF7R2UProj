#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "EndSequencerParticleActor.generated.h"

UCLASS(Blueprintable, NotPlaceable)
class ENDGAME_API AEndSequencerParticleActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath ResourcePath;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ResourceName;
    
public:
    AEndSequencerParticleActor(const FObjectInitializer& ObjectInitializer);

};

