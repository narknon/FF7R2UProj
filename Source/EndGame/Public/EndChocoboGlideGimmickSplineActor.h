#pragma once
#include "CoreMinimal.h"
#include "EndChocoboGlideGimmickSplineActorBase.h"
#include "EndChocoboGlideGimmickSplineActor.generated.h"

class AActor;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndChocoboGlideGimmickSplineActor : public AEndChocoboGlideGimmickSplineActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* TargetActor;
    
public:
    AEndChocoboGlideGimmickSplineActor(const FObjectInitializer& ObjectInitializer);

};

