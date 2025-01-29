#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEquipmentCategoryMain.h"
#include "EPlayerType.h"
#include "EndPlayerStatus.h"
#include "EndDataObjectEquipmentAccessor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Layout/Geometry.h"
#include "EEndBattleDamageSourcePowerType.h"
#include "EndMenuBPAPI.generated.h"

class UEndListBox;
class UEndMainMateriaListBoxWindow;
class UEndVirtualScrollBox;
class UUserWidget;
class UWorld;

UCLASS(Blueprintable)
class UEndMenuBPAPI : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UEndMenuBPAPI();

    UFUNCTION(BlueprintCallable)
    static void UpdateLinkedMateria(const TArray<UEndMainMateriaListBoxWindow*>& MateriaLists);
    
    UFUNCTION(BlueprintCallable)
    static void SetIgnoreRepeatKey(const UEndVirtualScrollBox* Widget, const FName& ButtonName);
    
    UFUNCTION(BlueprintCallable)
    static void SetIgnoreListRepeatKey(const UEndListBox* Widget, const FName& ButtonName);
    
    UFUNCTION(BlueprintCallable)
    static void ResetLinkedMateria(const TArray<UEndMainMateriaListBoxWindow*>& MateriaLists);
    
    UFUNCTION(BlueprintCallable)
    static void BPViewportToLocal(UWorld* World, const FGeometry& Geometry, FVector2D ViewportPosition, FVector2D& LocalCoordinate);
    
    UFUNCTION(BlueprintCallable)
    static void BPViewportToAbsolute(UWorld* World, const FGeometry& Geometry, FVector2D ViewportPosition, FVector2D& AbsoluteCoordinate);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetupStatusPanel(UUserWidget* TopStatus, EPlayerType PlayerType, EPlayerType LeaderType);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetupStatus(UUserWidget* TopStatus, EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetupLeaderLabel(UUserWidget* TopStatus, EPlayerType PlayerType, EPlayerType LeaderType);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetupBillboard(UUserWidget* TopStatus, EPlayerType PlayerType, bool enableReleaseSlate);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerMP(EPlayerType Type, int32 MP);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerMaxMP(EPlayerType Type, int32 MaxHp);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerLimitMax(EPlayerType Type, int32 LimitMax);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerLimitLevelMax(EPlayerType Type, int32 LimitLevelMax);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerLimitLevel(EPlayerType Type, int32 LimitLevel);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerLimit(EPlayerType Type, int32 Limit);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerLevel(EPlayerType Type, int32 Level);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerHPMax(EPlayerType Type, int32 HP);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerHP(EPlayerType Type, int32 HP);
    
    UFUNCTION(BlueprintCallable)
    static void BPSetPlayerExperience(EPlayerType Type, int32 Exp);
    
    UFUNCTION(BlueprintCallable)
    static void BPLocalToViewport(UWorld* World, const FGeometry& Geometry, FVector2D LocalCoordinate, FVector2D& ScreenPosition, FVector2D& ViewportPosition);
    
    UFUNCTION(BlueprintCallable)
    static bool BPIsCharacterDead(EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerVitality(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerStrength(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static FEndPlayerStatus BPGetPlayerStatusWithMateria(EPlayerType PlayerType, int32 OrigMateriaIndex, int32 TargetMateriaIndex, int32 SlotIndex, EEquipmentCategoryMain materiaEquipType);
    
    UFUNCTION(BlueprintCallable)
    static FEndPlayerStatus BPGetPlayerStatusWithEquipment(EPlayerType PlayerType, EEquipmentCategoryMain EquipType, const FName& EquipID, int32 EquipmentIndexToEquip);
    
    UFUNCTION(BlueprintCallable)
    static FEndPlayerStatus BPGetPlayerStatus(EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerSpirit(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerPhysicsDefense(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerPhysicsAttack(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerMP(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerMaxMP(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerMagicDefense(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerMagicAttack(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerMagic(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerLuck(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerLimitMax(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerLimitLevelMax(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerLimitLevel(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerLimit(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerLevel(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerHPMax(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerHP(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerExperienceNext(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerExperienceBase(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerExperience(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetPlayerDexterity(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static FName BPGetMemberName(EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    static FString BPGetLastName(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static FString BPGetFirstName(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetFinalPower(EPlayerType PlayerType, int32 PowerValue, EEndBattleDamageSourcePowerType PowerType);
    
    UFUNCTION(BlueprintCallable)
    static FEndDataObjectEquipmentAccessor BPGetCurrentEquipment(EPlayerType PlayerType, EEquipmentCategoryMain EquipType);
    
    UFUNCTION(BlueprintCallable)
    static int32 BPGetCurrentChapter(FName& ChapterID);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FName> BPGetAllChapters();
    
    UFUNCTION(BlueprintCallable)
    static void BPAbsoluteToViewport(UWorld* World, const FGeometry& Geometry, FVector2D AbsoluteCoordinate, FVector2D& ScreenPosition, FVector2D& ViewportPosition);
    
};

