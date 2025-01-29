#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEndAnimalRunTeamMode.h"
#include "ETeamType.h"
#include "Templates/SubclassOf.h"
#include "EndAnimalRunAIDirector.generated.h"

class AEndCharacterBase;
class UEndAnimalRunAIParameterBase;

UCLASS(Blueprintable)
class AEndAnimalRunAIDirector : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ShootableDistanceToBall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ShootableHeightToBall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ShootableBallSpeedLimitV;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ShootableAngleCheckDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ShootableAngleCharacterToBall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> RestPoints;
    
    AEndAnimalRunAIDirector(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void SetOverrideParameter(FName CharacterName, TSubclassOf<UEndAnimalRunAIParameterBase> OverrideParameterClass);
    
    UFUNCTION(BlueprintCallable)
    void SetLockTarget(FName CharacterName, ETeamType TeamType);
    
    UFUNCTION(BlueprintCallable)
    void SetAnimationPlayRate(FName CharacterName, float PlayRate);
    
    UFUNCTION(BlueprintCallable)
    void ResetOverrideParameter(FName CharacterName);
    
    UFUNCTION(BlueprintCallable)
    void ResetAnimationPlayRate(FName CharacterName);
    
public:
    UFUNCTION(BlueprintCallable)
    void RequestChangeMode(ETeamType TeamType, EEndAnimalRunTeamMode Mode);
    
private:
    UFUNCTION(BlueprintCallable)
    void RemoveAttachEffect(int32 HandleId);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnWildModeElapsedSecond(ETeamType TeamType, int32 ElapsedSecond);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnGoal(ETeamType TeamType, int32 Score);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnFinalize();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndMiniGame();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnElapsedSecond(int32 ElapsedSecond);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangeMode(ETeamType TeamType, EEndAnimalRunTeamMode Mode);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetTeamRank(ETeamType TeamType) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    EEndAnimalRunTeamMode GetTeamMode(ETeamType TeamType) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacterBase* GetRunWildAICharacter(FName CharacterName) const;
    
private:
    UFUNCTION(BlueprintCallable)
    void ChangeDefaultParameter(FName CharacterName, TSubclassOf<UEndAnimalRunAIParameterBase> DefaultParameterClass);
    
    UFUNCTION(BlueprintCallable)
    void AddAttachEffect(FName EffectName, FName CharacterName, FName AttachSocketNam, int32& OutHandleId);
    
};

