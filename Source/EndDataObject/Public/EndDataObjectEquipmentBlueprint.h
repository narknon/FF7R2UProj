#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EndDataObjectEquipmentAccessor.h"
#include "EndDataObjectEquipmentBlueprint.generated.h"

UCLASS(Blueprintable)
class UEndDataObjectEquipmentBlueprint : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UEndDataObjectEquipmentBlueprint();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetVitalityScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetVitalityAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetUpgradeID(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetStrengthScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetStrengthAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetStatusChangeResistSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStatusChangeResist(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSpiritScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSpiritAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSpecialResistSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetSpecialResist(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillTextLabelSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetSkillTextLabel(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillEffectValueSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetSkillEffectValue(const FEndDataObjectEquipmentAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillEffectTypeSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillEffectType(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillEffectTextInfoIDSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetSkillEffectTextInfoID(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillEffectNameSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetSkillEffectName(const FEndDataObjectEquipmentAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillCoreSlotNum(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillCoreSlotMaxSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillCoreSlotMax(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillConditionValueSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetSkillConditionValue(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSkillConditionTypeSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetSkillConditionType(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetPropertyResist1(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetPropertyResist0(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetOverrideGuardLoopSequeceName(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetOverrideGuardEndSequeceName(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetOverrideGuardBeginSequeceName(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetOverrideBurstAbilityText(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetOverrideBurstAbilityHelpText(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetNormalAttackReach(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMPMaxScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMPMaxAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetMovieName(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetModelMateriaIndexSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetModelMateriaIndex(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetMateriaSlotSingle(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMateriaSlotModifySize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetMateriaSlotModify(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetMateriaSlotDouble(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetMateriaGrowScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMagicScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMagicDefenseScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMagicDefenseAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMagicAttackScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMagicAttackAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMagicAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetLuckScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetLuckAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetLongAttackRange(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetLearningFlag(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetLearningCounterID(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetLearningCondUseCount(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetLearningConditionValueSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetLearningConditionValue(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetLearningConditionTypeSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetLearningConditionType(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetLearningConditionText(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetLearningCondAddPoint(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHPMaxScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHPMaxAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetFieldAttackStateTriggerId(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetDexterityScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetDexterityAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetDefenseScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetDefenseAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCriticalHitRateScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCriticalHitRateAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCharaSpecIDSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCharaSpecID(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCanEquipSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCanEquip(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetBurstAbilityID(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetBreakDead(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAttributeResistSize(const FEndDataObjectEquipmentAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAttributeResist(const FEndDataObjectEquipmentAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAttackScale(const FEndDataObjectEquipmentAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAttackAdd(const FEndDataObjectEquipmentAccessor& Instance);
    
};

