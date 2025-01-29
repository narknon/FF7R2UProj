#include "EndMenuBPAPI.h"

UEndMenuBPAPI::UEndMenuBPAPI() {
}

void UEndMenuBPAPI::UpdateLinkedMateria(const TArray<UEndMainMateriaListBoxWindow*>& MateriaLists) {
}

void UEndMenuBPAPI::SetIgnoreRepeatKey(const UEndVirtualScrollBox* Widget, const FName& ButtonName) {
}

void UEndMenuBPAPI::SetIgnoreListRepeatKey(const UEndListBox* Widget, const FName& ButtonName) {
}

void UEndMenuBPAPI::ResetLinkedMateria(const TArray<UEndMainMateriaListBoxWindow*>& MateriaLists) {
}

void UEndMenuBPAPI::BPViewportToLocal(UWorld* World, const FGeometry& Geometry, FVector2D ViewportPosition, FVector2D& LocalCoordinate) {
}

void UEndMenuBPAPI::BPViewportToAbsolute(UWorld* World, const FGeometry& Geometry, FVector2D ViewportPosition, FVector2D& AbsoluteCoordinate) {
}

void UEndMenuBPAPI::BPSetupStatusPanel(UUserWidget* TopStatus, EPlayerType PlayerType, EPlayerType LeaderType) {
}

void UEndMenuBPAPI::BPSetupStatus(UUserWidget* TopStatus, EPlayerType PlayerType) {
}

void UEndMenuBPAPI::BPSetupLeaderLabel(UUserWidget* TopStatus, EPlayerType PlayerType, EPlayerType LeaderType) {
}

void UEndMenuBPAPI::BPSetupBillboard(UUserWidget* TopStatus, EPlayerType PlayerType, bool enableReleaseSlate) {
}

void UEndMenuBPAPI::BPSetPlayerMP(EPlayerType Type, int32 MP) {
}

void UEndMenuBPAPI::BPSetPlayerMaxMP(EPlayerType Type, int32 MaxHp) {
}

void UEndMenuBPAPI::BPSetPlayerLimitMax(EPlayerType Type, int32 LimitMax) {
}

void UEndMenuBPAPI::BPSetPlayerLimitLevelMax(EPlayerType Type, int32 LimitLevelMax) {
}

void UEndMenuBPAPI::BPSetPlayerLimitLevel(EPlayerType Type, int32 LimitLevel) {
}

void UEndMenuBPAPI::BPSetPlayerLimit(EPlayerType Type, int32 Limit) {
}

void UEndMenuBPAPI::BPSetPlayerLevel(EPlayerType Type, int32 Level) {
}

void UEndMenuBPAPI::BPSetPlayerHPMax(EPlayerType Type, int32 HP) {
}

void UEndMenuBPAPI::BPSetPlayerHP(EPlayerType Type, int32 HP) {
}

void UEndMenuBPAPI::BPSetPlayerExperience(EPlayerType Type, int32 Exp) {
}

void UEndMenuBPAPI::BPLocalToViewport(UWorld* World, const FGeometry& Geometry, FVector2D LocalCoordinate, FVector2D& ScreenPosition, FVector2D& ViewportPosition) {
}

bool UEndMenuBPAPI::BPIsCharacterDead(EPlayerType PlayerType) {
    return false;
}

int32 UEndMenuBPAPI::BPGetPlayerVitality(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerStrength(EPlayerType Type) {
    return 0;
}

FEndPlayerStatus UEndMenuBPAPI::BPGetPlayerStatusWithMateria(EPlayerType PlayerType, int32 OrigMateriaIndex, int32 TargetMateriaIndex, int32 SlotIndex, EEquipmentCategoryMain materiaEquipType) {
    return FEndPlayerStatus{};
}

FEndPlayerStatus UEndMenuBPAPI::BPGetPlayerStatusWithEquipment(EPlayerType PlayerType, EEquipmentCategoryMain EquipType, const FName& EquipID, int32 EquipmentIndexToEquip) {
    return FEndPlayerStatus{};
}

FEndPlayerStatus UEndMenuBPAPI::BPGetPlayerStatus(EPlayerType PlayerType) {
    return FEndPlayerStatus{};
}

int32 UEndMenuBPAPI::BPGetPlayerSpirit(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerPhysicsDefense(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerPhysicsAttack(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerMP(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerMaxMP(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerMagicDefense(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerMagicAttack(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerMagic(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerLuck(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerLimitMax(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerLimitLevelMax(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerLimitLevel(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerLimit(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerLevel(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerHPMax(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerHP(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerExperienceNext(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerExperienceBase(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerExperience(EPlayerType Type) {
    return 0;
}

int32 UEndMenuBPAPI::BPGetPlayerDexterity(EPlayerType Type) {
    return 0;
}

FName UEndMenuBPAPI::BPGetMemberName(EPlayerType PlayerType) {
    return NAME_None;
}

FString UEndMenuBPAPI::BPGetLastName(EPlayerType Type) {
    return TEXT("");
}

FString UEndMenuBPAPI::BPGetFirstName(EPlayerType Type) {
    return TEXT("");
}

int32 UEndMenuBPAPI::BPGetFinalPower(EPlayerType PlayerType, int32 PowerValue, EEndBattleDamageSourcePowerType PowerType) {
    return 0;
}

FEndDataObjectEquipmentAccessor UEndMenuBPAPI::BPGetCurrentEquipment(EPlayerType PlayerType, EEquipmentCategoryMain EquipType) {
    return FEndDataObjectEquipmentAccessor{};
}

int32 UEndMenuBPAPI::BPGetCurrentChapter(FName& ChapterID) {
    return 0;
}

TArray<FName> UEndMenuBPAPI::BPGetAllChapters() {
    return TArray<FName>();
}

void UEndMenuBPAPI::BPAbsoluteToViewport(UWorld* World, const FGeometry& Geometry, FVector2D AbsoluteCoordinate, FVector2D& ScreenPosition, FVector2D& ViewportPosition) {
}


