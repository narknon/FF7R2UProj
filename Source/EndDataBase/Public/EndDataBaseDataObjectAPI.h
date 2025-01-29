#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EDataObjectType.h"
#include "EEndDataObjectDebugFlag.h"
#include "EEndFavPointSortType.h"
#include "EEquipmentType.h"
#include "EPlayerType.h"
#include "EndDataBaseDataObjectAPI.generated.h"

UCLASS(Blueprintable)
class ENDDATABASE_API UEndDataBaseDataObjectAPI : public UObject {
    GENERATED_BODY()
public:
    UEndDataBaseDataObjectAPI();

    UFUNCTION(BlueprintCallable)
    static void SetDebugFlag(EEndDataObjectDebugFlag Flag);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsExistDataObjectFromTypeBP(EDataObjectType Type);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsExistDataObjectBP();
    
    UFUNCTION(BlueprintCallable)
    static bool IsDebugFlag(EEndDataObjectDebugFlag Flag);
    
    UFUNCTION(BlueprintCallable)
    static TMap<EPlayerType, FName> GetWeaponNameMap();
    
    UFUNCTION(BlueprintCallable)
    static FName GetTestPlayModeTitleLocation(const FName& TableID);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FName> GetTestPlayModeSettingDataObjectIds();
    
    UFUNCTION(BlueprintCallable)
    static FName GetTestPlayModeSettingDataName(const FName& TableID);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FString> GetTestCutSceneNameList(const FString& LocationName);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FString> GetTestCutSceneEnviSetNameList(const TArray<FString>& CutSceneNames);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetResidentParameterStringBP(const FName ID, const FString& DefaultValue);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetResidentParameterNameBP(const FName ID, FName DefaultValue);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetResidentParameterIntegerBP(const FName ID, int32 DefaultValue);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetResidentParameterFloatBP(const FName ID, float DefaultValue);
    
    UFUNCTION(BlueprintCallable)
    static FName GetResidentID();
    
    UFUNCTION(BlueprintCallable)
    static TArray<EPlayerType> GetPlayerTypeListSortFavPointBP(const TArray<EPlayerType>& InList, EEndFavPointSortType sortType);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FString> GetLocationSlotList(const FString& LocationName);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FName> GetLocationPresetList(const FString& LocationName);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FString> GetLocationNames();
    
    UFUNCTION(BlueprintCallable)
    static TArray<FString> GetLocationNameDetails();
    
    UFUNCTION(BlueprintCallable)
    static FName GetLocationIdFromLocationWorkId(FName dataObjectId);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FString> GetLocationDetails();
    
    UFUNCTION(BlueprintCallable)
    static TArray<FString> GetFieldTestLocationNameDetails(bool bWithBack);
    
    UFUNCTION(BlueprintCallable)
    static TArray<EEquipmentType> GetEquipmentTypeList();
    
    UFUNCTION(BlueprintCallable)
    static FName GetDebugID();
    
    UFUNCTION(BlueprintCallable)
    static TArray<FString> GetChapterList(const FString& LocationName);
    
    UFUNCTION(BlueprintCallable)
    static TMap<EPlayerType, FName> GetActorNameMap();
    
    UFUNCTION(BlueprintCallable)
    static void ClearDebugFlag(EEndDataObjectDebugFlag Flag);
    
};

