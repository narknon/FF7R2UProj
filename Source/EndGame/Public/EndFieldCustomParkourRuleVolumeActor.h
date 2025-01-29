#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndFieldActionRuntimeCustomRuleVolumeInfo.h"
#include "EndFieldCustomParkourRuleVolumeActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndFieldCustomParkourRuleVolumeActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldActionRuntimeCustomRuleVolumeInfo RuntimeVolumeInfo;
    
public:
    AEndFieldCustomParkourRuleVolumeActor(const FObjectInitializer& ObjectInitializer);

};

