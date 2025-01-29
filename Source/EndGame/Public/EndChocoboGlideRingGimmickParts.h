#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "EndActorBaseInterface.h"
#include "EndChocoboGlideRingGimmickParts.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndChocoboGlideRingGimmickParts : public AActor, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RingEffectName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ProjectionEffectName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform RingEffectOffset;
    
public:
    AEndChocoboGlideRingGimmickParts(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

