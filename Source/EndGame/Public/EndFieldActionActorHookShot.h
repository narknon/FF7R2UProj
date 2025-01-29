#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EHookShotSeType.h"
#include "EndFieldActionActorHookShot.generated.h"

UCLASS(Blueprintable)
class AEndFieldActionActorHookShot : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EHookShotSeType HitSeType;
    
    AEndFieldActionActorHookShot(const FObjectInitializer& ObjectInitializer);

};

