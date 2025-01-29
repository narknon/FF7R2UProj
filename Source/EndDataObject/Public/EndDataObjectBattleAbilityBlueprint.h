#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EndDataObjectBattleAbilityAccessor.h"
#include "EndDataObjectBattleAbilityBlueprint.generated.h"

UCLASS(Blueprintable)
class UEndDataObjectBattleAbilityBlueprint : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UEndDataObjectBattleAbilityBlueprint();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetUseSoundResourceName(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetUseSoundResourceCategory(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetUsePlace(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetUniqueID(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTeleportType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetTeleportParam(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetTeleportMinDistance(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTargetCount(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTargetCorrectionDirectionImmediatelyType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTargetCloseMove(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTargetAimPosition(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStrengthenNumber(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSortId(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetSkeletonControlType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetShowNameSecond(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetShowName(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetSameCharacterDamageHitDamageCoefficientMin(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetSameCharacterDamageHitDamageCoefficient(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetResourceNameSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetResourceName(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetResourceIDSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetResourceID(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetReplaceDamageSourceID(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetReactionTypeSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetReactionType(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetReactionParameterValueSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetReactionParameterValue(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetReactionParameterStringSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetReactionParameterString(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetReactionInfluenceID(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetReactionConditionSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetReactionConditionParameterValueSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetReactionConditionParameterValue(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetReactionConditionNotifyIndexSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetReactionConditionNotifyIndex(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetReactionCondition(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetRange(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetName(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMP(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetKeepValue(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetInputBufferTime(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetForceDamageDisplayToOne(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintPure)
    static int64 GetFlag0(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetExplanation(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDistFeelType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDamageCreateMoveCollisionObjectOff(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCommandType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCommandTargetType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCastMagicEffectType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCancelNumberSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCancelNumber(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCameraSequenceNotify(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCameraSequenceID(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetATB(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetAnimResourceReferenceBattleCharaSpecID(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetAnimationUpperBodyName(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAnimationStringSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetAnimationString(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAnimationSelectTypeSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAnimationSelectType(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAnimationParameterSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetAnimationParameter(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAnimationBoneFilterIndexBits0(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAfterWalkType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAfterTeleportRotationType(const FEndDataObjectBattleAbilityAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAddAnimationPlayIntervalSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetAddAnimationPlayInterval(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAddAnimationPlayCountSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAddAnimationPlayCount(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAddAnimationNameSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetAddAnimationName(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAddAnimationIndexSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAddAnimationIndex(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAddAnimationEndBaseSize(const FEndDataObjectBattleAbilityAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAddAnimationEndBase(const FEndDataObjectBattleAbilityAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetActionCategory(const FEndDataObjectBattleAbilityAccessor& Instance);
    
};

