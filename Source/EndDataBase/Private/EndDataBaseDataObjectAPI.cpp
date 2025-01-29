#include "EndDataBaseDataObjectAPI.h"

UEndDataBaseDataObjectAPI::UEndDataBaseDataObjectAPI() {
}

void UEndDataBaseDataObjectAPI::SetDebugFlag(EEndDataObjectDebugFlag Flag) {
}

bool UEndDataBaseDataObjectAPI::IsExistDataObjectFromTypeBP(EDataObjectType Type) {
    return false;
}

bool UEndDataBaseDataObjectAPI::IsExistDataObjectBP() {
    return false;
}

bool UEndDataBaseDataObjectAPI::IsDebugFlag(EEndDataObjectDebugFlag Flag) {
    return false;
}

TMap<EPlayerType, FName> UEndDataBaseDataObjectAPI::GetWeaponNameMap() {
    return TMap<EPlayerType, FName>();
}

FName UEndDataBaseDataObjectAPI::GetTestPlayModeTitleLocation(const FName& TableID) {
    return NAME_None;
}

TArray<FName> UEndDataBaseDataObjectAPI::GetTestPlayModeSettingDataObjectIds() {
    return TArray<FName>();
}

FName UEndDataBaseDataObjectAPI::GetTestPlayModeSettingDataName(const FName& TableID) {
    return NAME_None;
}

TArray<FString> UEndDataBaseDataObjectAPI::GetTestCutSceneNameList(const FString& LocationName) {
    return TArray<FString>();
}

TArray<FString> UEndDataBaseDataObjectAPI::GetTestCutSceneEnviSetNameList(const TArray<FString>& CutSceneNames) {
    return TArray<FString>();
}

FString UEndDataBaseDataObjectAPI::GetResidentParameterStringBP(const FName ID, const FString& DefaultValue) {
    return TEXT("");
}

FName UEndDataBaseDataObjectAPI::GetResidentParameterNameBP(const FName ID, FName DefaultValue) {
    return NAME_None;
}

int32 UEndDataBaseDataObjectAPI::GetResidentParameterIntegerBP(const FName ID, int32 DefaultValue) {
    return 0;
}

float UEndDataBaseDataObjectAPI::GetResidentParameterFloatBP(const FName ID, float DefaultValue) {
    return 0.0f;
}

FName UEndDataBaseDataObjectAPI::GetResidentID() {
    return NAME_None;
}

TArray<EPlayerType> UEndDataBaseDataObjectAPI::GetPlayerTypeListSortFavPointBP(const TArray<EPlayerType>& InList, EEndFavPointSortType sortType) {
    return TArray<EPlayerType>();
}

TArray<FString> UEndDataBaseDataObjectAPI::GetLocationSlotList(const FString& LocationName) {
    return TArray<FString>();
}

TArray<FName> UEndDataBaseDataObjectAPI::GetLocationPresetList(const FString& LocationName) {
    return TArray<FName>();
}

TArray<FString> UEndDataBaseDataObjectAPI::GetLocationNames() {
    return TArray<FString>();
}

TArray<FString> UEndDataBaseDataObjectAPI::GetLocationNameDetails() {
    return TArray<FString>();
}

FName UEndDataBaseDataObjectAPI::GetLocationIdFromLocationWorkId(FName dataObjectId) {
    return NAME_None;
}

TArray<FString> UEndDataBaseDataObjectAPI::GetLocationDetails() {
    return TArray<FString>();
}

TArray<FString> UEndDataBaseDataObjectAPI::GetFieldTestLocationNameDetails(bool bWithBack) {
    return TArray<FString>();
}

TArray<EEquipmentType> UEndDataBaseDataObjectAPI::GetEquipmentTypeList() {
    return TArray<EEquipmentType>();
}

FName UEndDataBaseDataObjectAPI::GetDebugID() {
    return NAME_None;
}

TArray<FString> UEndDataBaseDataObjectAPI::GetChapterList(const FString& LocationName) {
    return TArray<FString>();
}

TMap<EPlayerType, FName> UEndDataBaseDataObjectAPI::GetActorNameMap() {
    return TMap<EPlayerType, FName>();
}

void UEndDataBaseDataObjectAPI::ClearDebugFlag(EEndDataObjectDebugFlag Flag) {
}


