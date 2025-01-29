#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndChocoboGlideGimmickActivateVolume.generated.h"

class AEndChocoboGlideGimmickSplineActorBase;

UCLASS(Blueprintable)
class ENDGAME_API AEndChocoboGlideGimmickActivateVolume : public AVolume {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AEndChocoboGlideGimmickSplineActorBase*> TargetActors;
    
public:
    AEndChocoboGlideGimmickActivateVolume(const FObjectInitializer& ObjectInitializer);

};

