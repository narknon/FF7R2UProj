#include "EndMenuAPI.h"

UEndMenuAPI::UEndMenuAPI() {
}

void UEndMenuAPI::UpdateWidgetTest() {
}

void UEndMenuAPI::UpdateMenu(float DeltaSeconds) {
}

bool UEndMenuAPI::SituationNameExists(const FString& TextId) {
    return false;
}

void UEndMenuAPI::ShowTalkLogs(UObject* WorldContextObject) {
}

void UEndMenuAPI::ShowSubtitle(UObject* WorldContextObject, const FString& TextId, bool bWaitKey, bool bArrowHidden, bool bInForce) {
}

void UEndMenuAPI::ShowSkippingIcon(UObject* WorldContextObject) {
}

void UEndMenuAPI::ShowPhotoSpotNotice() {
}

void UEndMenuAPI::ShowPauseMenu(UObject* WorldContextObject, EEndMenuPauseMode Mode) {
}

void UEndMenuAPI::ShowMovie(UObject* WorldContextObject, UMaterialInterface* Material) {
}

UUserWidget* UEndMenuAPI::ShowMessageWindow(UObject* WorldContextObject, const FString& TextId, const TArray<FString>& OptionTextIds, EEndMenuMessageWindowFlags Flags) {
    return NULL;
}

void UEndMenuAPI::ShowMessageLogs(UObject* WorldContextObject) {
}

void UEndMenuAPI::ShowLocationName(UObject* WorldContextObject, const FString& TextId, const FString& EnTextId) {
}

void UEndMenuAPI::ShowLoadingScreenForChocoboFastTravel(UObject* WorldContextObject, const FString& ChocoboText, FName LocationId) {
}

void UEndMenuAPI::ShowLoadingScreen(UObject* WorldContextObject, FName LocationId, bool ShowLocationTip) {
}

void UEndMenuAPI::ShowLoadingIcon(UObject* WorldContextObject) {
}

UUserWidget* UEndMenuAPI::ShowFieldTargetIcon(UObject* WorldContextObject, FVector WorldPosition, EEndMenuFieldTargetState State, EEndMenuFieldTargetIconType aType, FName InName) {
    return NULL;
}

void UEndMenuAPI::ShowFieldPane(EEndMenuFieldPaneType Type) {
}

void UEndMenuAPI::ShowFieldMenu(UObject* WorldContextObject) {
}

void UEndMenuAPI::ShowDebugListBox(UObject* WorldContextObject, const TArray<FString>& InStringArray, float InWidth, float InHeight, bool InSingleNodeAutoClick, FString& OutString, FLatentActionInfo LatentInfo) {
}

void UEndMenuAPI::ShowDamagePopupMessage(UObject* WorldContextObject, AActor* Actor, FVector WorldPosition, EEndMenuPopupMessageKind Kind, const FEndMenuDamageInfo& Info) {
}

void UEndMenuAPI::ShowChapterName(UObject* WorldContextObject, const FString& TextId, const FString& EnTextId, float LoopTime) {
}

UUserWidget* UEndMenuAPI::ShowBattleTargetIcon(UObject* WorldContextObject, FVector WorldPosition, EEndMenuBattleTargetState State) {
    return NULL;
}

UUserWidget* UEndMenuAPI::ShowBattlePlayerStatusWindow() {
    return NULL;
}

UUserWidget* UEndMenuAPI::ShowBattleEnemyStatusWindow() {
    return NULL;
}

void UEndMenuAPI::ShowBattleEnemyOutsideWindow() {
}

void UEndMenuAPI::ShowAreaName(UObject* WorldContextObject, const FString& TextId) {
}

void UEndMenuAPI::SetVirtualAcceptRight(bool bRight) {
}

void UEndMenuAPI::SetNavimapInBattle(bool bInInBattle) {
}

void UEndMenuAPI::SetFocusToWidget(UWidget* InWidget) {
}

void UEndMenuAPI::SetFocusBrushBySlateColor(FSlateColor InColor) {
}

void UEndMenuAPI::SetFieldTargetIconRangeText(UUserWidget* Icon, int32 aRange) {
}

void UEndMenuAPI::SetFieldTargetIconRange(UUserWidget* Icon, float aRange) {
}

void UEndMenuAPI::SetFieldTargetIconPosition(UUserWidget* Icon, FVector WorldPosition) {
}

void UEndMenuAPI::SetFieldTargetIconHoldGauge(UUserWidget* Icon, float aGauge) {
}

void UEndMenuAPI::SetFieldMenuInBattle(bool bInInBattle) {
}

void UEndMenuAPI::SetFadeFilterVisibility(FName Name, bool bVisible) {
}

bool UEndMenuAPI::SetBattleTargetIconPosition(UUserWidget* Icon, FVector WorldPosition) {
    return false;
}

void UEndMenuAPI::SetBattleTargetIconActor(UUserWidget* Icon, AActor* Actor) {
}

void UEndMenuAPI::SetBattleEnemyStatusWindowPosition(UUserWidget* Icon, FVector WorldPosition) {
}

void UEndMenuAPI::RemoveFadeFilter(FName Name, int32 removeDelayFrame) {
}

void UEndMenuAPI::RefreshStatusWindow() {
}

bool UEndMenuAPI::NeedMagnifyFont() {
    return false;
}

bool UEndMenuAPI::Need4KFont() {
    return false;
}

TSoftClassPtr<UObject> UEndMenuAPI::MakeSoftClassPtr(const FString& inString) {
    return NULL;
}

bool UEndMenuAPI::LocationNameExists(const FString& TextId) {
    return false;
}

bool UEndMenuAPI::Key_IsVirtualBack(const FKey& Key) {
    return false;
}

bool UEndMenuAPI::Key_IsVirtualAccept(const FKey& Key) {
    return false;
}

bool UEndMenuAPI::IsSubtitleClosed(const FString& TextId) {
    return false;
}

bool UEndMenuAPI::IsPauseMenuClosed() {
    return false;
}

bool UEndMenuAPI::IsMessageWindowClosed(UUserWidget* Widget) {
    return false;
}

bool UEndMenuAPI::IsJoinLeftUpdate() {
    return false;
}

bool UEndMenuAPI::IsFieldMenuStatus(EEndMenuFieldMenuStatus Status) {
    return false;
}

bool UEndMenuAPI::IsFieldMenuShortcutActive() {
    return false;
}

bool UEndMenuAPI::IsFieldMenuLinkupWindowOpen() {
    return false;
}

bool UEndMenuAPI::IsFieldMenuLinkupActive() {
    return false;
}

bool UEndMenuAPI::IsFadeFilterDuringAnimation(FName Name) {
    return false;
}

bool UEndMenuAPI::IsFadeFilter(FName Name) {
    return false;
}

bool UEndMenuAPI::IsBattleTargetIconActor(AActor* Actor) {
    return false;
}

void UEndMenuAPI::HideTalkLogs() {
}

void UEndMenuAPI::HideSubtitle(const FString& TextId) {
}

void UEndMenuAPI::HideSkippingIcon() {
}

void UEndMenuAPI::HidePhotoSpotNotice() {
}

void UEndMenuAPI::HidePauseMenu() {
}

void UEndMenuAPI::HideMovie() {
}

void UEndMenuAPI::HideMessageWindow(UUserWidget* Widget) {
}

void UEndMenuAPI::HideMessageLogs() {
}

void UEndMenuAPI::HideLoadingScreen() {
}

void UEndMenuAPI::HideLoadingIcon() {
}

void UEndMenuAPI::HideFieldTargetIcon(UUserWidget* Icon) {
}

void UEndMenuAPI::HideFieldPane(EEndMenuFieldPaneType Type, bool bCommandReset) {
}

void UEndMenuAPI::HideFieldMenu() {
}

void UEndMenuAPI::HideFieldAction() {
}

void UEndMenuAPI::HideBattleTargetIcon(UUserWidget* Icon) {
}

void UEndMenuAPI::HideBattlePlayerStatusWindow() {
}

void UEndMenuAPI::HideBattleEnemyStatusWindow() {
}

void UEndMenuAPI::HideBattleEnemyOutsideWindow() {
}

bool UEndMenuAPI::HasFadeFiltersDuringAnimation() {
    return false;
}

bool UEndMenuAPI::HasFadeFilters() {
    return false;
}

void UEndMenuAPI::GetWidgetAnimations(UWidget* InWidget, TArray<FName>& OutNames) {
}

UWidgetAnimation* UEndMenuAPI::GetWidgetAnimationByName(UWidget* InWidget, FName InName) {
    return NULL;
}

FString UEndMenuAPI::GetString(const FString& TextId) {
    return TEXT("");
}

int32 UEndMenuAPI::GetMessageWindowSelectedIndex(UUserWidget* Widget) {
    return 0;
}

FString UEndMenuAPI::GetLocationNameTextID(FName LocationId) {
    return TEXT("");
}

EEndMenuIconKind UEndMenuAPI::GetItemMessageLogIconKind(FName ItemId) {
    return EEndMenuIconKind::None;
}

EEndMenuFieldTargetState UEndMenuAPI::GetFieldTargetIconState(UUserWidget* Icon) {
    return EEndMenuFieldTargetState::None;
}

bool UEndMenuAPI::GetFadeFilterVisibility(FName Name) {
    return false;
}

void UEndMenuAPI::GetFadeFilterNames(TArray<FName>& OutNames) {
}

FLinearColor UEndMenuAPI::GetFadeFilterCurrentColor(FName Name) {
    return FLinearColor{};
}

EEndMenuBattleTargetState UEndMenuAPI::GetBattleTargetIconState(UUserWidget* Icon) {
    return EEndMenuBattleTargetState::None;
}

FString UEndMenuAPI::GetBattleSimulatorVersionString() {
    return TEXT("");
}

UUserWidget* UEndMenuAPI::CreateWidgetFromPack(UObject* WorldContextObject, FName LevelName, FName ResourceName) {
    return NULL;
}

void UEndMenuAPI::ClearTalkLogs() {
}

void UEndMenuAPI::ClearMessageWindows() {
}

void UEndMenuAPI::ClearLocationTitles() {
}

void UEndMenuAPI::ClearFadeFilters() {
}

bool UEndMenuAPI::ChapterNameExists(const FString& TextId) {
    return false;
}

void UEndMenuAPI::ChangeFieldTargetIconState(UUserWidget* Icon, EEndMenuFieldTargetState State) {
}

void UEndMenuAPI::ChangeFieldTargetIconButton(UUserWidget* Icon, EEndMenuFieldTargetIconType aButtonType) {
}

void UEndMenuAPI::ChangeFadeFilter(FName Name, FLinearColor ToColor, float FadeTime, bool bAutoDestroy, bool bPauseable) {
}

void UEndMenuAPI::ChangeBattleTargetIconState(UUserWidget* Icon, EEndMenuBattleTargetState State) {
}

void UEndMenuAPI::BPShowVisionIcon(UObject* WorldContextObject) {
}

void UEndMenuAPI::BPShowUIFilterWindow(UObject* WorldContextObject, EEndMenuUIFilterType aFilterType) {
}

void UEndMenuAPI::BPShowTalkSelect(UObject* WorldContextObject, EEndMenuTalkSelectWindowType aWindowType) {
}

void UEndMenuAPI::BPShowNavimap(UObject* WorldContextObject) {
}

void UEndMenuAPI::BPShowGameOver(UObject* WorldContextObject) {
}

void UEndMenuAPI::BPShowFieldStaminaIcon(UObject* WorldContextObject) {
}

void UEndMenuAPI::BPShowFieldInputGuidelineWindow(UObject* WorldContextObject, EEndMenuInputGuidelineType aType) {
}

void UEndMenuAPI::BPShowFieldAction(const FString& aActionTextId) {
}

void UEndMenuAPI::BPShowEventProgress(UObject* WorldContextObject, const FString& aShowText) {
}

void UEndMenuAPI::BPShowDataAccessIcon(UObject* WorldContextObject) {
}

void UEndMenuAPI::BPShowCountdown(UObject* WorldContextObject, float SetTime) {
}

void UEndMenuAPI::BPShowCharacterReJoin(UObject* WorldContextObject, bool bIsLeftOut) {
}

void UEndMenuAPI::BPShowCharacterJoin(UObject* WorldContextObject, EPlayerType PlayerType, bool bIsIn) {
}

void UEndMenuAPI::BPShowCaution(UObject* WorldContextObject) {
}

void UEndMenuAPI::BPShowBossStatus(UObject* WorldContextObject) {
}

void UEndMenuAPI::BPShowBattleTutorialWindow(UObject* WorldContextObject, FName aKey) {
}

UUserWidget* UEndMenuAPI::BPShowBattleLockonMarkerIcon(UObject* WorldContextObject, FVector WorldPosition, EEndMenuLockonMarkerType aType) {
    return NULL;
}

void UEndMenuAPI::BPShowBattleEscape(UObject* WorldContextObject) {
}

void UEndMenuAPI::BPSetFieldStaminaSpeed(float aSpeedQt) {
}

void UEndMenuAPI::BPSetFieldStaminaGauge(float aGaugeQt) {
}

void UEndMenuAPI::BPSetCountdownTime(float SetTime) {
}

void UEndMenuAPI::BPSetCautionQuantity(float aQT) {
}

void UEndMenuAPI::BPSetBossHPGauge(float aHP) {
}

void UEndMenuAPI::BPSetBossDamageLidHP(float aHP) {
}

void UEndMenuAPI::BPHideVisionIcon() {
}

void UEndMenuAPI::BPHideUIFilterWindow(EEndMenuUIFilterType aFilterType) {
}

void UEndMenuAPI::BPHideTalkSelect() {
}

void UEndMenuAPI::BPHideNavimap() {
}

void UEndMenuAPI::BPHideGameOver() {
}

void UEndMenuAPI::BPHideFieldStaminaIcon() {
}

void UEndMenuAPI::BPHideFieldInputGuidelineWindow() {
}

void UEndMenuAPI::BPHideEventProgress(bool aAnimation) {
}

void UEndMenuAPI::BPHideDataAccessIcon() {
}

void UEndMenuAPI::BPHideCountdown(bool aHideFailed) {
}

void UEndMenuAPI::BPHideCharacterReJoin() {
}

void UEndMenuAPI::BPHideCharacterJoin() {
}

void UEndMenuAPI::BPHideCaution(bool aInBattle) {
}

void UEndMenuAPI::BPHideBossStatus() {
}

void UEndMenuAPI::BPHideBattleTutorialWindow(FName aKey) {
}

void UEndMenuAPI::BPHideBattleEscape(bool aInBattle) {
}

bool UEndMenuAPI::AreaNameExists(const FString& TextId) {
    return false;
}

void UEndMenuAPI::AddTalkLogByTextId(const FString& TextId, float WaitSeconds) {
}

void UEndMenuAPI::AddMessageLog_AnyThread(EEndMenuIconKind Icon, const FString& Message, EEndMenuLogEffectKind Effect, EEndMenuLogColorKind Color, EEndMenuLogOptionFlags Option) {
}

void UEndMenuAPI::AddFadeFilter(UObject* WorldContextObject, FName Name, int32 ZOrder, FLinearColor FromColor, FLinearColor ToColor, float FadeTime, bool bAutoDestroy, bool bPauseable) {
}


