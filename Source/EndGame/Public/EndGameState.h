#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/LatentActionManager.h"
#include "EEndSystemPauseMenuKind.h"
#include "EGameMode.h"
#include "EGamePause.h"
#include "EGameState.h"
#include "EGameStatus.h"
#include "EGameTrigger.h"
#include "GameStateChange.h"
#include "EndGameState.generated.h"

class UObject;

UCLASS(Blueprintable)
class ENDGAME_API AEndGameState : public AGameStateBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EGameState GameState;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FGameStateChange GameStateChange[64];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GameStateChangeCount;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EGameMode GameMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActiveLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ActiveLocationSlot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 PrevActiveLocationSlot;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bRequestActiveLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RequestTargetLocationStr;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bRequestTruthLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RequestTruthLocationStr;
    
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 GameStatus;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 GamePause;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 RequestGamePauseOn;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 RequestGamePauseOff;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndSystemPauseMenuKind NextPauseMenuKind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool HideWorld;
    
    AEndGameState(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetRequestGamePauseOn(EGamePause Pause);
    
    UFUNCTION(BlueprintCallable)
    void SetGameStatus(EGameStatus Status, bool Set);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void SendGameTrigger(const UObject* WorldContextObject, EGameTrigger Trigger, EGameState toState, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, Exec)
    static void OnDebugPauseFrameSkip();
    
    UFUNCTION(BlueprintCallable, Exec)
    static void OnDebugPauseEnable();
    
    UFUNCTION(BlueprintCallable)
    bool IsGameStatus(EGameStatus Status);
    
    UFUNCTION(BlueprintCallable)
    bool IsGamePause();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    EGameState GetGameState() const;
    
    UFUNCTION(BlueprintCallable)
    float GetGameSpeed();
    
    UFUNCTION(BlueprintCallable)
    void ActivateLocation(FName TargetLocation);
    
};

