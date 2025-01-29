#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EndDataObjectPlayerTableAccessor.h"
#include "EndDataObjectPlayerTableBlueprint.generated.h"

UCLASS(Blueprintable)
class UEndDataObjectPlayerTableBlueprint : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UEndDataObjectPlayerTableBlueprint();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetWeaponUpgradeTreeLevelFormat(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetTextID(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetTargetSuppLocID(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetSwitchFavPointResidentWorkStoryFlagID(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetSwitchFavPointResidentWorkID(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSeeChangeClothSize(const FEndDataObjectPlayerTableAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetSeeChangeCloth(const FEndDataObjectPlayerTableAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetRegularMemberJoinFlag(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetPlayerType(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetPlayerParameterStringFormat(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetPlayerFavRankFormat(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPlayerCharaSpecSize(const FEndDataObjectPlayerTableAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetPlayerCharaSpec(const FEndDataObjectPlayerTableAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetPCReinforcedFormat(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetNotifySPUpMessage(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetNotifyLevelUpMessage(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetMateriaOpenMenuFlag(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetLastBattleInfoResidentParameterID(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetIgnoreBattleReward(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetFavPointPriority(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetFavMapIconID(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetExcludeMateriaListFlag(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetExcludeEquipmentListFlag(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetEventStoryFlagSize(const FEndDataObjectPlayerTableAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetEventStoryFlag(const FEndDataObjectPlayerTableAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetEventCharaSpecSize(const FEndDataObjectPlayerTableAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetEventCharaSpec(const FEndDataObjectPlayerTableAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetEquipmentOpenMenuFlag(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetEquipListAddFlag(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetConfigFavPointStoryFlagChapter12(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetConfigFavPointStoryFlag(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetChangeWeaponStoryFlagSize(const FEndDataObjectPlayerTableAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetChangeWeaponStoryFlag(const FEndDataObjectPlayerTableAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetChangeWeaponCharaSpecSize(const FEndDataObjectPlayerTableAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetChangeWeaponCharaSpec(const FEndDataObjectPlayerTableAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCautionAttackResponseArea(const FEndDataObjectPlayerTableAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetActorName(const FEndDataObjectPlayerTableAccessor& Instance);
    
};

