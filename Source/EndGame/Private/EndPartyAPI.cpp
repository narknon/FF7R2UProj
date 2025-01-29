#include "EndPartyAPI.h"

UEndPartyAPI::UEndPartyAPI() {
}

void UEndPartyAPI::StartPlayerStream(EPlayerStreamType Type) {
}

void UEndPartyAPI::SetPlayerStatus(EPlayerType Type, EPlayerStatus Status) {
}

void UEndPartyAPI::SetPlayerActor(EEquipmentType Equipment, EPlayerType Type, AActor* Actor) {
}

void UEndPartyAPI::SetPartyLeaderType(EPlayerType InLeader, bool bIsInputTrigered, bool bForce) {
}

void UEndPartyAPI::SetPartyLeader(AActor* InLeader, bool bIsInputTrigered) {
}

void UEndPartyAPI::SetBattleSlotIndex(EPlayerType Type, int32 Slot) {
}

void UEndPartyAPI::SetBattleAway(EPlayerType Type, bool bFlag) {
}

void UEndPartyAPI::ResetPlayerPosition() {
}

bool UEndPartyAPI::IsReserveMember(EPlayerType Type) {
    return false;
}

bool UEndPartyAPI::IsFinishPlayerStream() {
    return false;
}

bool UEndPartyAPI::IsBattleMember(EPlayerType Type) {
    return false;
}

bool UEndPartyAPI::IsAllPartyMember(EPlayerType Type) {
    return false;
}

void UEndPartyAPI::InitPartyLevel(const UObject* WorldContextObject) {
}

EPlayerType UEndPartyAPI::GetReserveMemberType(int32 Slot) {
    return EPlayerType::CLOUD;
}

TArray<AEndCharacter*> UEndPartyAPI::GetReserveMembers() {
    return TArray<AEndCharacter*>();
}

int32 UEndPartyAPI::GetReserveMemberCount() {
    return 0;
}

AEndCharacter* UEndPartyAPI::GetReserveMember(int32 Index) {
    return NULL;
}

EPlayerStatus UEndPartyAPI::GetPlayerStatus(EPlayerType Type) {
    return EPlayerStatus::EPlayerType_NONE;
}

FName UEndPartyAPI::GetPlayerActorName(EPlayerType Type) {
    return NAME_None;
}

AActor* UEndPartyAPI::GetPlayerActor(EEquipmentType Equipment, EPlayerType Type) {
    return NULL;
}

int32 UEndPartyAPI::GetPartyMemberCountForPartyStatus(EPlayerStatus findPlayerStatus) {
    return 0;
}

EPlayerType UEndPartyAPI::GetPartyLeaderType() {
    return EPlayerType::CLOUD;
}

AActor* UEndPartyAPI::GetPartyLeaderOrVehicle(bool bIsFatMoogleIgnore) {
    return NULL;
}

FName UEndPartyAPI::GetPartyLeaderName() {
    return NAME_None;
}

TArray<EPlayerType> UEndPartyAPI::GetEquipmentMenuMembers() {
    return TArray<EPlayerType>();
}

int32 UEndPartyAPI::GetBattleSlotIndex(EPlayerType Type) {
    return 0;
}

EPlayerType UEndPartyAPI::GetBattleMemberType(int32 Slot) {
    return EPlayerType::CLOUD;
}

TArray<AEndCharacter*> UEndPartyAPI::GetBattleMembers() {
    return TArray<AEndCharacter*>();
}

int32 UEndPartyAPI::GetBattleMemberCount() {
    return 0;
}

AEndCharacter* UEndPartyAPI::GetBattleMember(int32 Index) {
    return NULL;
}

bool UEndPartyAPI::GetBattleAway(EPlayerType Type) {
    return false;
}

EPlayerType UEndPartyAPI::GetAllPartyMemberType(int32 Slot) {
    return EPlayerType::CLOUD;
}

TArray<AEndCharacter*> UEndPartyAPI::GetAllPartyMembers() {
    return TArray<AEndCharacter*>();
}

int32 UEndPartyAPI::GetAllPartyMemberCount() {
    return 0;
}

AEndCharacter* UEndPartyAPI::GetAllPartyMember(int32 Index) {
    return NULL;
}

int32 UEndPartyAPI::GetAliveBattleMemberCount() {
    return 0;
}

void UEndPartyAPI::CallTeleported(const FVector& NewLocation, AActor* InLeader) {
}


