#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndBattleExitBattleSceneType.h"
#include "EndSoundHandle.h"
#include "EndBattleTalkOnEndBattleActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndBattleTalkOnEndBattleActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DelayMinSeconds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DelayMaxSeconds;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndSoundHandle AudioComponent;
    
public:
    AEndBattleTalkOnEndBattleActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void PlayVoice(bool bUnuseDefaultDelay, float OverrideDelayMinSeconds, float OverrideDelayMaxSeconds, FName VoiceSetId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndBattle(const TArray<FName>& TerritoryIDList, EndBattleExitBattleSceneType BattleExitType);
    
};

