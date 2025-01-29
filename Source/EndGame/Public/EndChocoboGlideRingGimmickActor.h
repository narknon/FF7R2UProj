#pragma once
#include "CoreMinimal.h"
#include "EndChocoboGlideGimmickSplineActorBase.h"
#include "Templates/SubclassOf.h"
#include "EndChocoboGlideRingGimmickActor.generated.h"

class AActor;
class AEndChocoboGlideRingGimmickParts;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndChocoboGlideRingGimmickActor : public AEndChocoboGlideGimmickSplineActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CharaSpecID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndChocoboGlideRingGimmickParts> RingPartsClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bMoveAtRingCenter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* RingActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* RingPartsActor;
    
public:
    AEndChocoboGlideRingGimmickActor(const FObjectInitializer& ObjectInitializer);

};

