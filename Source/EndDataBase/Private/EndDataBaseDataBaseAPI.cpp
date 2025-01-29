#include "EndDataBaseDataBaseAPI.h"

UEndDataBaseDataBaseAPI::UEndDataBaseDataBaseAPI() {
}

void UEndDataBaseDataBaseAPI::StopPlayTime() {
}

void UEndDataBaseDataBaseAPI::StartStreamMateriaModel() {
}

void UEndDataBaseDataBaseAPI::StartPlayTime() {
}

void UEndDataBaseDataBaseAPI::SetupInitialParameter(FName debugPartyListDataTableId) {
}

void UEndDataBaseDataBaseAPI::SetTestPlayModeTableID(FName setTableID) {
}

void UEndDataBaseDataBaseAPI::SetStoryFlagBP(const FName& StoryFlagId, bool Value) {
}

void UEndDataBaseDataBaseAPI::SetResidentWorkInteger(const FName ResidentWorkID, int32 Value) {
}

void UEndDataBaseDataBaseAPI::SetResidentWorkFloat(const FName ResidentWorkID, float Value) {
}

void UEndDataBaseDataBaseAPI::SetLocationWorkInteger(FName LocationWorkID, int32 Value) {
}

void UEndDataBaseDataBaseAPI::SetLocationWorkFloat(FName LocationWorkID, float Value) {
}

void UEndDataBaseDataBaseAPI::SetDefaultPartyLeaderTypeBP(EPlayerType Type) {
}

void UEndDataBaseDataBaseAPI::SetDefaultBattleLeaderTypeBP(EPlayerType Type) {
}

void UEndDataBaseDataBaseAPI::SetDebugChapterID(const FString& DebugChapterID) {
}

bool UEndDataBaseDataBaseAPI::IsStoryFlag(const FName& StoryFlagId) {
    return false;
}

bool UEndDataBaseDataBaseAPI::IsFinishStreamMateriaModel() {
    return false;
}

bool UEndDataBaseDataBaseAPI::IsDifficulty(EDifficultyType Difficulty) {
    return false;
}

bool UEndDataBaseDataBaseAPI::IsDebugPartyList() {
    return false;
}

bool UEndDataBaseDataBaseAPI::IsClassic() {
    return false;
}

void UEndDataBaseDataBaseAPI::Hoge09() {
}

void UEndDataBaseDataBaseAPI::Hoge08() {
}

void UEndDataBaseDataBaseAPI::Hoge07() {
}

void UEndDataBaseDataBaseAPI::Hoge06() {
}

void UEndDataBaseDataBaseAPI::Hoge05() {
}

void UEndDataBaseDataBaseAPI::Hoge04() {
}

void UEndDataBaseDataBaseAPI::Hoge03() {
}

void UEndDataBaseDataBaseAPI::Hoge02() {
}

void UEndDataBaseDataBaseAPI::Hoge01() {
}

void UEndDataBaseDataBaseAPI::Hoge00() {
}

bool UEndDataBaseDataBaseAPI::GetUpdatePlayTimeFlag() {
    return false;
}

FName UEndDataBaseDataBaseAPI::GetTestPlayModeTableID() {
    return NAME_None;
}

int32 UEndDataBaseDataBaseAPI::GetResidentWorkInteger(const FName ResidentWorkID) {
    return 0;
}

float UEndDataBaseDataBaseAPI::GetResidentWorkFloat(const FName ResidentWorkID) {
    return 0.0f;
}

FRotator UEndDataBaseDataBaseAPI::GetPlayerRotation(EPlayerType Type) {
    return FRotator{};
}

FVector UEndDataBaseDataBaseAPI::GetPlayerPosition(EPlayerType Type) {
    return FVector{};
}

int32 UEndDataBaseDataBaseAPI::GetLocationWorkInteger(FName LocationWorkID) {
    return 0;
}

float UEndDataBaseDataBaseAPI::GetLocationWorkFloat(FName LocationWorkID) {
    return 0.0f;
}

int32 UEndDataBaseDataBaseAPI::GetItemNumBP(int32 UniqueId) {
    return 0;
}

EPlayerType UEndDataBaseDataBaseAPI::GetDefaultPartyLeaderTypeBP() {
    return EPlayerType::CLOUD;
}

EPlayerType UEndDataBaseDataBaseAPI::GetDefaultBattleLeaderTypeBP() {
    return EPlayerType::CLOUD;
}

FName UEndDataBaseDataBaseAPI::GetDebugChapterID() {
    return NAME_None;
}

int32 UEndDataBaseDataBaseAPI::GetChapterProgress() {
    return 0;
}

void UEndDataBaseDataBaseAPI::EnemyBook_IncrementKillCount_BP(FName enemyBookTableId) {
}


