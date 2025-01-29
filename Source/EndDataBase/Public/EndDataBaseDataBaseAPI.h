#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EDifficultyType.h"
#include "EPlayerType.h"
#include "EndDataBaseDataBaseAPI.generated.h"

UCLASS(Blueprintable)
class ENDDATABASE_API UEndDataBaseDataBaseAPI : public UObject {
    GENERATED_BODY()
public:
    UEndDataBaseDataBaseAPI();

    UFUNCTION(BlueprintCallable)
    static void StopPlayTime();
    
    UFUNCTION(BlueprintCallable)
    static void StartStreamMateriaModel();
    
    UFUNCTION(BlueprintCallable)
    static void StartPlayTime();
    
    UFUNCTION(BlueprintCallable)
    static void SetupInitialParameter(FName debugPartyListDataTableId);
    
    UFUNCTION(BlueprintCallable)
    static void SetTestPlayModeTableID(FName setTableID);
    
    UFUNCTION(BlueprintCallable)
    static void SetStoryFlagBP(const FName& StoryFlagId, bool Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetResidentWorkInteger(const FName ResidentWorkID, int32 Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetResidentWorkFloat(const FName ResidentWorkID, float Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetLocationWorkInteger(FName LocationWorkID, int32 Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetLocationWorkFloat(FName LocationWorkID, float Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetDefaultPartyLeaderTypeBP(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static void SetDefaultBattleLeaderTypeBP(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static void SetDebugChapterID(const FString& DebugChapterID);
    
    UFUNCTION(BlueprintCallable)
    static bool IsStoryFlag(const FName& StoryFlagId);
    
    UFUNCTION(BlueprintCallable)
    static bool IsFinishStreamMateriaModel();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDifficulty(EDifficultyType Difficulty);
    
    UFUNCTION(BlueprintCallable)
    static bool IsDebugPartyList();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsClassic();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge09();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge08();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge07();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge06();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge05();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge04();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge03();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge02();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge01();
    
    UFUNCTION(BlueprintCallable)
    static void Hoge00();
    
    UFUNCTION(BlueprintCallable)
    static bool GetUpdatePlayTimeFlag();
    
    UFUNCTION(BlueprintCallable)
    static FName GetTestPlayModeTableID();
    
    UFUNCTION(BlueprintCallable)
    static int32 GetResidentWorkInteger(const FName ResidentWorkID);
    
    UFUNCTION(BlueprintCallable)
    static float GetResidentWorkFloat(const FName ResidentWorkID);
    
    UFUNCTION(BlueprintCallable)
    static FRotator GetPlayerRotation(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static FVector GetPlayerPosition(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetLocationWorkInteger(FName LocationWorkID);
    
    UFUNCTION(BlueprintCallable)
    static float GetLocationWorkFloat(FName LocationWorkID);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetItemNumBP(int32 UniqueId);
    
    UFUNCTION(BlueprintCallable)
    static EPlayerType GetDefaultPartyLeaderTypeBP();
    
    UFUNCTION(BlueprintCallable)
    static EPlayerType GetDefaultBattleLeaderTypeBP();
    
    UFUNCTION(BlueprintCallable)
    static FName GetDebugChapterID();
    
    UFUNCTION(BlueprintCallable)
    static int32 GetChapterProgress();
    
    UFUNCTION(BlueprintCallable)
    static void EnemyBook_IncrementKillCount_BP(FName enemyBookTableId);
    
};

