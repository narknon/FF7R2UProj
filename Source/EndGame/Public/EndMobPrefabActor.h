#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "EEndMobPrefabStateTrigger.h"
#include "EWeaponSlot.h"
#include "EndMobPrefabRandomAnimationExecuteItem.h"
#include "EndMobPrefabRegistry.h"
#include "EndMobPrefabRegistryOverride.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndOptimizeAnimActorInterface.h"
#include "EndMobPrefabActor.generated.h"

class AEndCharacterBase;
class AEndSkeletalMeshActorBase;
class UEndMobPrefabCommand;

UCLASS(Blueprintable)
class ENDGAME_API AEndMobPrefabActor : public AActor, public IEndOptimizeAnimActorInterface, public IEndNaviMapDataProviderInterface, public INavRelevantInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMobPrefabRegistry> Registries;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndMobPrefabRegistryOverride> RegistryOverrides;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> RestorePhysicsAccessorIds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MobIds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bHasMoveArround;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableAutoSetIgnorePushActorToOther;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bGraphicsModeCastShadow;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bPerformanceModeCastShadow;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UEndMobPrefabCommand*> CommandList;
    
    AEndMobPrefabActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetWeaponRegistryWeaponClass(FName MobId, EWeaponSlot WeaponSlot, TSoftClassPtr<AEndSkeletalMeshActorBase> WeaponClass);
    
    UFUNCTION(BlueprintCallable)
    void SetWeaponRegistryAttachSocketName(FName MobId, EWeaponSlot WeaponSlot, FName AttachSocketName);
    
    UFUNCTION(BlueprintCallable)
    void SetWeaponRegistryAttachOffset(FName MobId, EWeaponSlot WeaponSlot, FVector AttachOffsetLocation, FRotator AttachOffsetRotation);
    
    UFUNCTION(BlueprintCallable)
    void SetRegistryMotionLookupTable(FName MobId, FName MotionName, FName ActualMotionName);
    
    UFUNCTION(BlueprintCallable)
    void SetRegistryInitialLoopMotionTimeLinkParentMobId(FName MobId, FName InitialLoopMotionTimeLinkParentMobId);
    
    UFUNCTION(BlueprintCallable)
    void SetRegistryInitialLoopMotionName(FName MobId, FName InitialLoopMotionName);
    
    UFUNCTION(BlueprintCallable)
    void SetRegistryInitialLookAtTargetMobId(FName MobId, FName InitialLookAtTargetMobId);
    
    UFUNCTION(BlueprintCallable)
    void SetRegistryInitialLookAtBlendRate(FName MobId, float InitialLookAtBlendRate);
    
    UFUNCTION(BlueprintCallable)
    void SetRegistryCharacterClass(FName MobId, TSoftClassPtr<AEndCharacterBase> CharacterClass);
    
    UFUNCTION(BlueprintCallable)
    void SetRegistryBoneFilterWhenMoving(FName MobId, FName MotionName, FName BoneFilter);
    
    UFUNCTION(BlueprintCallable)
    void SetRegistryAnimSetName(FName MobId, FName AnimSetName);
    
    UFUNCTION(BlueprintCallable)
    void RemoveWeaponRegistry(FName MobId, EWeaponSlot WeaponSlot);
    
    UFUNCTION(BlueprintCallable)
    void RemoveRegistryMotionLookupTable(FName MobId, FName MotionName);
    
    UFUNCTION(BlueprintCallable)
    void RemoveRegistryBoneFilterWhenMoving(FName MobId, FName MotionName);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnPreUpdateRegistry();
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void CreateMobCommand();
    
    UFUNCTION(BlueprintCallable)
    int32 AddTimerConditionCommand(FName MobId, int32 ChainCommandId, FVector2D WaitTimeRange);
    
    UFUNCTION(BlueprintCallable)
    int32 AddTimeLink8AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange, bool bAllowMotionCancel, FName LinkedMobId2, FName LinkedMotion2, FName LinkedReplaceBaseMotion2, FName LinkedMobId3, FName LinkedMotion3, FName LinkedReplaceBaseMotion3, FName LinkedMobId4, FName LinkedMotion4, FName LinkedReplaceBaseMotion4, FName LinkedMobId5, FName LinkedMotion5, FName LinkedReplaceBaseMotion5, FName LinkedMobId6, FName LinkedMotion6, FName LinkedReplaceBaseMotion6, FName LinkedMobId7, FName LinkedMotion7, FName LinkedReplaceBaseMotion7, FName LinkedMobId8, FName LinkedMotion8, FName LinkedReplaceBaseMotion8);
    
    UFUNCTION(BlueprintCallable)
    int32 AddTimeLink4AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange, bool bAllowMotionCancel, FName LinkedMobId2, FName LinkedMotion2, FName LinkedReplaceBaseMotion2, FName LinkedMobId3, FName LinkedMotion3, FName LinkedReplaceBaseMotion3, FName LinkedMobId4, FName LinkedMotion4, FName LinkedReplaceBaseMotion4);
    
    UFUNCTION(BlueprintCallable)
    int32 AddTimeLink2AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange, bool bAllowMotionCancel, FName LinkedMobId2, FName LinkedMotion2, FName LinkedReplaceBaseMotion2);
    
    UFUNCTION(BlueprintCallable)
    int32 AddRandomConditionCommand(FName MobId, int32 ChainCommandId, float Rate);
    
    UFUNCTION(BlueprintCallable)
    int32 AddRandomAnimationWithLookAtExecuteCommand(FName MobId, int32 ChainCommandId, TArray<FEndMobPrefabRandomAnimationExecuteItem> Items, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange);
    
    UFUNCTION(BlueprintCallable)
    int32 AddRandomAnimationExecuteCommand(FName MobId, int32 ChainCommandId, TArray<FEndMobPrefabRandomAnimationExecuteItem> Items, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange);
    
    UFUNCTION(BlueprintCallable)
    int32 AddRandom8AnimationWithLookAtExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion1, float Weight1, bool bAllowMotionCancel1, FName Motion2, float Weight2, bool bAllowMotionCancel2, FName Motion3, float Weight3, bool bAllowMotionCancel3, FName Motion4, float Weight4, bool bAllowMotionCancel4, FName Motion5, float Weight5, bool bAllowMotionCancel5, FName Motion6, float Weight6, bool bAllowMotionCancel6, FName Motion7, float Weight7, bool bAllowMotionCancel7, FName Motion8, float Weight8, bool bAllowMotionCancel8, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange);
    
    UFUNCTION(BlueprintCallable)
    int32 AddRandom8AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion1, float Weight1, bool bAllowMotionCancel1, FName Motion2, float Weight2, bool bAllowMotionCancel2, FName Motion3, float Weight3, bool bAllowMotionCancel3, FName Motion4, float Weight4, bool bAllowMotionCancel4, FName Motion5, float Weight5, bool bAllowMotionCancel5, FName Motion6, float Weight6, bool bAllowMotionCancel6, FName Motion7, float Weight7, bool bAllowMotionCancel7, FName Motion8, float Weight8, bool bAllowMotionCancel8, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange);
    
    UFUNCTION(BlueprintCallable)
    int32 AddRandom4AnimationWithLookAtExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion1, float Weight1, bool bAllowMotionCancel1, FName Motion2, float Weight2, bool bAllowMotionCancel2, FName Motion3, float Weight3, bool bAllowMotionCancel3, FName Motion4, float Weight4, bool bAllowMotionCancel4, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange);
    
    UFUNCTION(BlueprintCallable)
    int32 AddRandom4AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion1, float Weight1, bool bAllowMotionCancel1, FName Motion2, float Weight2, bool bAllowMotionCancel2, FName Motion3, float Weight3, bool bAllowMotionCancel3, FName Motion4, float Weight4, bool bAllowMotionCancel4, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange);
    
    UFUNCTION(BlueprintCallable)
    int32 AddPlayingAnimationConditionCommand(FName MobId, int32 ChainCommandId, FName Motion0, FName Motion1, FName Motion2, FName Motion3);
    
    UFUNCTION(BlueprintCallable)
    int32 AddPartyPositionConditionCommand(FName MobId, int32 ChainCommandId, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime, FName TargetName);
    
    UFUNCTION(BlueprintCallable)
    int32 AddOnceConditionCommand(FName MobId, int32 ChainCommandId, bool bAllowReset);
    
    UFUNCTION(BlueprintCallable)
    int32 AddMoveArroundExecuteCommand(FName MobId, int32 ChainCommandId, float MoveRadius, float RunRate, FVector2D MoveDistanceRange, FVector2D MoveWaitTimeRange, float MoveTimeOut, float CautionDistance);
    
    UFUNCTION(BlueprintCallable)
    int32 AddLookAtStartExecuteCommand(FName MobId, int32 ChainCommandId, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway);
    
    UFUNCTION(BlueprintCallable)
    int32 AddLookAtExecuteCommand(FName MobId, int32 ChainCommandId, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange);
    
    UFUNCTION(BlueprintCallable)
    int32 AddLookAtEndExecuteCommand(FName MobId, int32 ChainCommandId);
    
    UFUNCTION(BlueprintCallable)
    int32 AddEventUnbindMessageCommand(FName MobId, int32 ChainCommandId);
    
    UFUNCTION(BlueprintCallable)
    int32 AddEventStateTriggerMessageCommand(FName MobId, int32 ChainCommandId, EEndMobPrefabStateTrigger Trigger);
    
    UFUNCTION(BlueprintCallable)
    int32 AddEmptyConditionCommand(FName MobId, int32 ChainCommandId);
    
    UFUNCTION(BlueprintCallable)
    int32 AddContactConditionCommand(FName MobId, int32 ChainCommandId, bool bForwardLeft, bool bForwardRight, bool bBackLeft, bool bBackRight, float ContinuationTime);
    
    UFUNCTION(BlueprintCallable)
    int32 AddContactAnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName ForwardLeftMotion, FName ForwardRightMotion, FName BackLeftMotion, FName BackRightMotion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange, bool bAllowMotionCancel);
    
    UFUNCTION(BlueprintCallable)
    int32 AddAutoReactionToPartyExecuteCommand(FName MobId, int32 ChainCommandId, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime, bool bFromCenter, FName TargetName, FName Motion, float BlendTime, FName ReplaceBaseMotion, FName OutMotion, float OutBlendTime, FName OutReplaceBaseMotion, bool bPlayMotionOnce);
    
    UFUNCTION(BlueprintCallable)
    int32 AddAutoLookAtPartyExecuteCommand(FName MobId, int32 ChainCommandId, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime, bool bFromCenter, FName TargetName, bool bLookAway);
    
    UFUNCTION(BlueprintCallable)
    int32 AddAutoLookAtActorExecuteCommand(FName MobId, int32 ChainCommandId, FName Actor0, FName Actor1, FName Actor2, FName Actor3, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime, bool bFromCenter);
    
    UFUNCTION(BlueprintCallable)
    int32 AddAnimationWithLookAtExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange, bool bAllowMotionCancel);
    
    UFUNCTION(BlueprintCallable)
    int32 AddAnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange, bool bAllowMotionCancel);
    
    UFUNCTION(BlueprintCallable)
    int32 AddAllowContactPropagateExecuteCommand(const TMap<FName, FName>& PropagateMotionTable, const TMap<FName, FName>& PropagateForwardLeftMotionTable, const TMap<FName, FName>& PropagateForawrdRightMotionTable, const TMap<FName, FName>& PropagateBackLeftMotionTable, const TMap<FName, FName>& PropagateBackRightMotionTable, FName MobId, int32 ChainCommandId, bool bAllowedDuringPlayMotion, FName ForwardLeftMotion, FName ForwardRightMotion, FName BackLeftMotion, FName BackRightMotion, float ContactMotionBlendTime, float PropagateMotionBlendTime, FName OutMotion, float OutBlendTime, FName OutReplaceBaseMotion);
    
    UFUNCTION(BlueprintCallable)
    int32 AddAllowContactExecuteCommand(FName MobId, int32 ChainCommandId, bool bAllowedDuringPlayMotion, FName ForwardLeftMotion, FName ForwardRightMotion, FName BackLeftMotion, FName BackRightMotion);
    
    UFUNCTION(BlueprintCallable)
    int32 AddActorPositionConditionCommand(FName MobId, int32 ChainCommandId, FName Actor0, FName Actor1, FName Actor2, FName Actor3, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime);
    

    // Fix for true pure virtual functions not being implemented
};

