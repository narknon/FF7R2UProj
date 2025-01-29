#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EPlayerType.h"
#include "Engine/LatentActionManager.h"
#include "InputCoreTypes.h"
#include "Styling/SlateColor.h"
#include "EEndMenuBattleTargetState.h"
#include "EEndMenuFieldMenuStatus.h"
#include "EEndMenuFieldPaneType.h"
#include "EEndMenuFieldTargetIconType.h"
#include "EEndMenuFieldTargetState.h"
#include "EEndMenuIconKind.h"
#include "EEndMenuInputGuidelineType.h"
#include "EEndMenuLockonMarkerType.h"
#include "EEndMenuLogColorKind.h"
#include "EEndMenuLogEffectKind.h"
#include "EEndMenuLogOptionFlags.h"
#include "EEndMenuMessageWindowFlags.h"
#include "EEndMenuPauseMode.h"
#include "EEndMenuPopupMessageKind.h"
#include "EEndMenuTalkSelectWindowType.h"
#include "EEndMenuUIFilterType.h"
#include "EndMenuDamageInfo.h"
#include "EndMenuAPI.generated.h"

class AActor;
class UMaterialInterface;
class UUserWidget;
class UWidget;
class UWidgetAnimation;

UCLASS(Blueprintable)
class ENDGAME_API UEndMenuAPI : public UObject {
    GENERATED_BODY()
public:
    UEndMenuAPI();

    UFUNCTION(BlueprintCallable)
    static void UpdateWidgetTest();
    
    UFUNCTION(BlueprintCallable)
    static void UpdateMenu(float DeltaSeconds);
    
    UFUNCTION(BlueprintCallable)
    static bool SituationNameExists(const FString& TextId);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowTalkLogs(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowSubtitle(UObject* WorldContextObject, const FString& TextId, bool bWaitKey, bool bArrowHidden, bool bInForce);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowSkippingIcon(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable)
    static void ShowPhotoSpotNotice();
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowPauseMenu(UObject* WorldContextObject, EEndMenuPauseMode Mode);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowMovie(UObject* WorldContextObject, UMaterialInterface* Material);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static UUserWidget* ShowMessageWindow(UObject* WorldContextObject, const FString& TextId, const TArray<FString>& OptionTextIds, EEndMenuMessageWindowFlags Flags);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowMessageLogs(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowLocationName(UObject* WorldContextObject, const FString& TextId, const FString& EnTextId);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowLoadingScreenForChocoboFastTravel(UObject* WorldContextObject, const FString& ChocoboText, FName LocationId);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowLoadingScreen(UObject* WorldContextObject, FName LocationId, bool ShowLocationTip);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowLoadingIcon(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static UUserWidget* ShowFieldTargetIcon(UObject* WorldContextObject, FVector WorldPosition, EEndMenuFieldTargetState State, EEndMenuFieldTargetIconType aType, FName InName);
    
    UFUNCTION(BlueprintCallable)
    static void ShowFieldPane(EEndMenuFieldPaneType Type);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowFieldMenu(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void ShowDebugListBox(UObject* WorldContextObject, const TArray<FString>& InStringArray, float InWidth, float InHeight, bool InSingleNodeAutoClick, FString& OutString, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowDamagePopupMessage(UObject* WorldContextObject, AActor* Actor, FVector WorldPosition, EEndMenuPopupMessageKind Kind, const FEndMenuDamageInfo& Info);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowChapterName(UObject* WorldContextObject, const FString& TextId, const FString& EnTextId, float LoopTime);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static UUserWidget* ShowBattleTargetIcon(UObject* WorldContextObject, FVector WorldPosition, EEndMenuBattleTargetState State);
    
    UFUNCTION(BlueprintCallable)
    static UUserWidget* ShowBattlePlayerStatusWindow();
    
    UFUNCTION(BlueprintCallable)
    static UUserWidget* ShowBattleEnemyStatusWindow();
    
    UFUNCTION(BlueprintCallable)
    static void ShowBattleEnemyOutsideWindow();
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void ShowAreaName(UObject* WorldContextObject, const FString& TextId);
    
    UFUNCTION(BlueprintCallable)
    static void SetVirtualAcceptRight(bool bRight);
    
    UFUNCTION(BlueprintCallable)
    static void SetNavimapInBattle(bool bInInBattle);
    
    UFUNCTION(BlueprintCallable)
    static void SetFocusToWidget(UWidget* InWidget);
    
    UFUNCTION(BlueprintCallable)
    static void SetFocusBrushBySlateColor(FSlateColor InColor);
    
    UFUNCTION(BlueprintCallable)
    static void SetFieldTargetIconRangeText(UUserWidget* Icon, int32 aRange);
    
    UFUNCTION(BlueprintCallable)
    static void SetFieldTargetIconRange(UUserWidget* Icon, float aRange);
    
    UFUNCTION(BlueprintCallable)
    static void SetFieldTargetIconPosition(UUserWidget* Icon, FVector WorldPosition);
    
    UFUNCTION(BlueprintCallable)
    static void SetFieldTargetIconHoldGauge(UUserWidget* Icon, float aGauge);
    
    UFUNCTION(BlueprintCallable)
    static void SetFieldMenuInBattle(bool bInInBattle);
    
    UFUNCTION(BlueprintCallable)
    static void SetFadeFilterVisibility(FName Name, bool bVisible);
    
    UFUNCTION(BlueprintCallable)
    static bool SetBattleTargetIconPosition(UUserWidget* Icon, FVector WorldPosition);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleTargetIconActor(UUserWidget* Icon, AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleEnemyStatusWindowPosition(UUserWidget* Icon, FVector WorldPosition);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveFadeFilter(FName Name, int32 removeDelayFrame);
    
    UFUNCTION(BlueprintCallable)
    static void RefreshStatusWindow();
    
    UFUNCTION(BlueprintCallable)
    static bool NeedMagnifyFont();
    
    UFUNCTION(BlueprintCallable)
    static bool Need4KFont();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TSoftClassPtr<UObject> MakeSoftClassPtr(const FString& inString);
    
    UFUNCTION(BlueprintCallable)
    static bool LocationNameExists(const FString& TextId);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool Key_IsVirtualBack(const FKey& Key);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool Key_IsVirtualAccept(const FKey& Key);
    
    UFUNCTION(BlueprintCallable)
    static bool IsSubtitleClosed(const FString& TextId);
    
    UFUNCTION(BlueprintCallable)
    static bool IsPauseMenuClosed();
    
    UFUNCTION(BlueprintCallable)
    static bool IsMessageWindowClosed(UUserWidget* Widget);
    
    UFUNCTION(BlueprintCallable)
    static bool IsJoinLeftUpdate();
    
    UFUNCTION(BlueprintCallable)
    static bool IsFieldMenuStatus(EEndMenuFieldMenuStatus Status);
    
    UFUNCTION(BlueprintCallable)
    static bool IsFieldMenuShortcutActive();
    
    UFUNCTION(BlueprintCallable)
    static bool IsFieldMenuLinkupWindowOpen();
    
    UFUNCTION(BlueprintCallable)
    static bool IsFieldMenuLinkupActive();
    
    UFUNCTION(BlueprintCallable)
    static bool IsFadeFilterDuringAnimation(FName Name);
    
    UFUNCTION(BlueprintCallable)
    static bool IsFadeFilter(FName Name);
    
    UFUNCTION(BlueprintCallable)
    bool IsBattleTargetIconActor(AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    static void HideTalkLogs();
    
    UFUNCTION(BlueprintCallable)
    static void HideSubtitle(const FString& TextId);
    
    UFUNCTION(BlueprintCallable)
    static void HideSkippingIcon();
    
    UFUNCTION(BlueprintCallable)
    static void HidePhotoSpotNotice();
    
    UFUNCTION(BlueprintCallable)
    static void HidePauseMenu();
    
    UFUNCTION(BlueprintCallable)
    static void HideMovie();
    
    UFUNCTION(BlueprintCallable)
    static void HideMessageWindow(UUserWidget* Widget);
    
    UFUNCTION(BlueprintCallable)
    static void HideMessageLogs();
    
    UFUNCTION(BlueprintCallable)
    static void HideLoadingScreen();
    
    UFUNCTION(BlueprintCallable)
    static void HideLoadingIcon();
    
    UFUNCTION(BlueprintCallable)
    static void HideFieldTargetIcon(UUserWidget* Icon);
    
    UFUNCTION(BlueprintCallable)
    static void HideFieldPane(EEndMenuFieldPaneType Type, bool bCommandReset);
    
    UFUNCTION(BlueprintCallable)
    static void HideFieldMenu();
    
    UFUNCTION(BlueprintCallable)
    static void HideFieldAction();
    
    UFUNCTION(BlueprintCallable)
    static void HideBattleTargetIcon(UUserWidget* Icon);
    
    UFUNCTION(BlueprintCallable)
    static void HideBattlePlayerStatusWindow();
    
    UFUNCTION(BlueprintCallable)
    static void HideBattleEnemyStatusWindow();
    
    UFUNCTION(BlueprintCallable)
    static void HideBattleEnemyOutsideWindow();
    
    UFUNCTION(BlueprintCallable)
    static bool HasFadeFiltersDuringAnimation();
    
    UFUNCTION(BlueprintCallable)
    static bool HasFadeFilters();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetWidgetAnimations(UWidget* InWidget, TArray<FName>& OutNames);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static UWidgetAnimation* GetWidgetAnimationByName(UWidget* InWidget, FName InName);
    
    UFUNCTION(BlueprintCallable)
    static FString GetString(const FString& TextId);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetMessageWindowSelectedIndex(UUserWidget* Widget);
    
    UFUNCTION(BlueprintCallable)
    static FString GetLocationNameTextID(FName LocationId);
    
    UFUNCTION(BlueprintCallable)
    static EEndMenuIconKind GetItemMessageLogIconKind(FName ItemId);
    
    UFUNCTION(BlueprintCallable)
    static EEndMenuFieldTargetState GetFieldTargetIconState(UUserWidget* Icon);
    
    UFUNCTION(BlueprintCallable)
    static bool GetFadeFilterVisibility(FName Name);
    
    UFUNCTION(BlueprintCallable)
    static void GetFadeFilterNames(TArray<FName>& OutNames);
    
    UFUNCTION(BlueprintCallable)
    static FLinearColor GetFadeFilterCurrentColor(FName Name);
    
    UFUNCTION(BlueprintCallable)
    static EEndMenuBattleTargetState GetBattleTargetIconState(UUserWidget* Icon);
    
    UFUNCTION(BlueprintCallable)
    static FString GetBattleSimulatorVersionString();
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static UUserWidget* CreateWidgetFromPack(UObject* WorldContextObject, FName LevelName, FName ResourceName);
    
    UFUNCTION(BlueprintCallable)
    static void ClearTalkLogs();
    
    UFUNCTION(BlueprintCallable)
    static void ClearMessageWindows();
    
    UFUNCTION(BlueprintCallable)
    static void ClearLocationTitles();
    
    UFUNCTION(BlueprintCallable)
    static void ClearFadeFilters();
    
    UFUNCTION(BlueprintCallable)
    static bool ChapterNameExists(const FString& TextId);
    
    UFUNCTION(BlueprintCallable)
    static void ChangeFieldTargetIconState(UUserWidget* Icon, EEndMenuFieldTargetState State);
    
    UFUNCTION(BlueprintCallable)
    static void ChangeFieldTargetIconButton(UUserWidget* Icon, EEndMenuFieldTargetIconType aButtonType);
    
    UFUNCTION(BlueprintCallable)
    static void ChangeFadeFilter(FName Name, FLinearColor ToColor, float FadeTime, bool bAutoDestroy, bool bPauseable);
    
    UFUNCTION(BlueprintCallable)
    static void ChangeBattleTargetIconState(UUserWidget* Icon, EEndMenuBattleTargetState State);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowVisionIcon(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowUIFilterWindow(UObject* WorldContextObject, EEndMenuUIFilterType aFilterType);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowTalkSelect(UObject* WorldContextObject, EEndMenuTalkSelectWindowType aWindowType);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowNavimap(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowGameOver(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowFieldStaminaIcon(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowFieldInputGuidelineWindow(UObject* WorldContextObject, EEndMenuInputGuidelineType aType);
    
    UFUNCTION(BlueprintCallable)
    static void BPShowFieldAction(const FString& aActionTextId);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowEventProgress(UObject* WorldContextObject, const FString& aShowText);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowDataAccessIcon(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowCountdown(UObject* WorldContextObject, float SetTime);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowCharacterReJoin(UObject* WorldContextObject, bool bIsLeftOut);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowCharacterJoin(UObject* WorldContextObject, EPlayerType PlayerType, bool bIsIn);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowCaution(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowBossStatus(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowBattleTutorialWindow(UObject* WorldContextObject, FName aKey);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static UUserWidget* BPShowBattleLockonMarkerIcon(UObject* WorldContextObject, FVector WorldPosition, EEndMenuLockonMarkerType aType);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void BPShowBattleEscape(UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetFieldStaminaSpeed(float aSpeedQt);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetFieldStaminaGauge(float aGaugeQt);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetCountdownTime(float SetTime);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetCautionQuantity(float aQT);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetBossHPGauge(float aHP);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetBossDamageLidHP(float aHP);
    
    UFUNCTION(BlueprintCallable)
    static void BPHideVisionIcon();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideUIFilterWindow(EEndMenuUIFilterType aFilterType);
    
    UFUNCTION(BlueprintCallable)
    static void BPHideTalkSelect();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideNavimap();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideGameOver();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideFieldStaminaIcon();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideFieldInputGuidelineWindow();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideEventProgress(bool aAnimation);
    
    UFUNCTION(BlueprintCallable)
    static void BPHideDataAccessIcon();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideCountdown(bool aHideFailed);
    
    UFUNCTION(BlueprintCallable)
    static void BPHideCharacterReJoin();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideCharacterJoin();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideCaution(bool aInBattle);
    
    UFUNCTION(BlueprintCallable)
    static void BPHideBossStatus();
    
    UFUNCTION(BlueprintCallable)
    static void BPHideBattleTutorialWindow(FName aKey);
    
    UFUNCTION(BlueprintCallable)
    static void BPHideBattleEscape(bool aInBattle);
    
    UFUNCTION(BlueprintCallable)
    static bool AreaNameExists(const FString& TextId);
    
    UFUNCTION(BlueprintCallable)
    static void AddTalkLogByTextId(const FString& TextId, float WaitSeconds);
    
    UFUNCTION(BlueprintCallable)
    static void AddMessageLog_AnyThread(EEndMenuIconKind Icon, const FString& Message, EEndMenuLogEffectKind Effect, EEndMenuLogColorKind Color, EEndMenuLogOptionFlags Option);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void AddFadeFilter(UObject* WorldContextObject, FName Name, int32 ZOrder, FLinearColor FromColor, FLinearColor ToColor, float FadeTime, bool bAutoDestroy, bool bPauseable);
    
};

