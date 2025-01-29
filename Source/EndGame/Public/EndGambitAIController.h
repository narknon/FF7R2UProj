#pragma once
#include "CoreMinimal.h"
#include "EGambitTargetLaneType.h"
#include "EndGambitMinigameAIControllerBase.h"
#include "EndGambitAIController.generated.h"

class AEndCharacter;

UCLASS(Blueprintable)
class ENDGAME_API AEndGambitAIController : public AEndGambitMinigameAIControllerBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_GeneratedLaneIdx;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAltAbility;
    
public:
    AEndGambitAIController(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetGroundMode();
    
    UFUNCTION(BlueprintCallable)
    void SetDisableLastActionFooter(bool bDisable);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStarted();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnRoleChange(FName ActionID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnGameSet(int32 endState);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetStageIndex() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacter* GetOwnerUnit();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetLastAction() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<AEndCharacter*> GetLaneUnits(EGambitTargetLaneType Lanetype, bool bOpposing);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    uint8 GetGeneratedLaneIdx() const;
    
    UFUNCTION(BlueprintCallable)
    void DeleteAttribute();
    
    UFUNCTION(BlueprintCallable)
    void AddLastGambitActionRemain();
    
};

