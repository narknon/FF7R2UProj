#include "EndMobPrefabActor.h"
#include "Components/SceneComponent.h"

AEndMobPrefabActor::AEndMobPrefabActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    this->bHasMoveArround = false;
    this->bEnableAutoSetIgnorePushActorToOther = true;
    this->bGraphicsModeCastShadow = true;
    this->bPerformanceModeCastShadow = true;
}

void AEndMobPrefabActor::SetWeaponRegistryWeaponClass(FName MobId, EWeaponSlot WeaponSlot, TSoftClassPtr<AEndSkeletalMeshActorBase> WeaponClass) {
}

void AEndMobPrefabActor::SetWeaponRegistryAttachSocketName(FName MobId, EWeaponSlot WeaponSlot, FName AttachSocketName) {
}

void AEndMobPrefabActor::SetWeaponRegistryAttachOffset(FName MobId, EWeaponSlot WeaponSlot, FVector AttachOffsetLocation, FRotator AttachOffsetRotation) {
}

void AEndMobPrefabActor::SetRegistryMotionLookupTable(FName MobId, FName MotionName, FName ActualMotionName) {
}

void AEndMobPrefabActor::SetRegistryInitialLoopMotionTimeLinkParentMobId(FName MobId, FName InitialLoopMotionTimeLinkParentMobId) {
}

void AEndMobPrefabActor::SetRegistryInitialLoopMotionName(FName MobId, FName InitialLoopMotionName) {
}

void AEndMobPrefabActor::SetRegistryInitialLookAtTargetMobId(FName MobId, FName InitialLookAtTargetMobId) {
}

void AEndMobPrefabActor::SetRegistryInitialLookAtBlendRate(FName MobId, float InitialLookAtBlendRate) {
}

void AEndMobPrefabActor::SetRegistryCharacterClass(FName MobId, TSoftClassPtr<AEndCharacterBase> CharacterClass) {
}

void AEndMobPrefabActor::SetRegistryBoneFilterWhenMoving(FName MobId, FName MotionName, FName BoneFilter) {
}

void AEndMobPrefabActor::SetRegistryAnimSetName(FName MobId, FName AnimSetName) {
}

void AEndMobPrefabActor::RemoveWeaponRegistry(FName MobId, EWeaponSlot WeaponSlot) {
}

void AEndMobPrefabActor::RemoveRegistryMotionLookupTable(FName MobId, FName MotionName) {
}

void AEndMobPrefabActor::RemoveRegistryBoneFilterWhenMoving(FName MobId, FName MotionName) {
}

void AEndMobPrefabActor::OnPreUpdateRegistry_Implementation() {
}

void AEndMobPrefabActor::CreateMobCommand_Implementation() {
}

int32 AEndMobPrefabActor::AddTimerConditionCommand(FName MobId, int32 ChainCommandId, FVector2D WaitTimeRange) {
    return 0;
}

int32 AEndMobPrefabActor::AddTimeLink8AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange, bool bAllowMotionCancel, FName LinkedMobId2, FName LinkedMotion2, FName LinkedReplaceBaseMotion2, FName LinkedMobId3, FName LinkedMotion3, FName LinkedReplaceBaseMotion3, FName LinkedMobId4, FName LinkedMotion4, FName LinkedReplaceBaseMotion4, FName LinkedMobId5, FName LinkedMotion5, FName LinkedReplaceBaseMotion5, FName LinkedMobId6, FName LinkedMotion6, FName LinkedReplaceBaseMotion6, FName LinkedMobId7, FName LinkedMotion7, FName LinkedReplaceBaseMotion7, FName LinkedMobId8, FName LinkedMotion8, FName LinkedReplaceBaseMotion8) {
    return 0;
}

int32 AEndMobPrefabActor::AddTimeLink4AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange, bool bAllowMotionCancel, FName LinkedMobId2, FName LinkedMotion2, FName LinkedReplaceBaseMotion2, FName LinkedMobId3, FName LinkedMotion3, FName LinkedReplaceBaseMotion3, FName LinkedMobId4, FName LinkedMotion4, FName LinkedReplaceBaseMotion4) {
    return 0;
}

int32 AEndMobPrefabActor::AddTimeLink2AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange, bool bAllowMotionCancel, FName LinkedMobId2, FName LinkedMotion2, FName LinkedReplaceBaseMotion2) {
    return 0;
}

int32 AEndMobPrefabActor::AddRandomConditionCommand(FName MobId, int32 ChainCommandId, float Rate) {
    return 0;
}

int32 AEndMobPrefabActor::AddRandomAnimationWithLookAtExecuteCommand(FName MobId, int32 ChainCommandId, TArray<FEndMobPrefabRandomAnimationExecuteItem> Items, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange) {
    return 0;
}

int32 AEndMobPrefabActor::AddRandomAnimationExecuteCommand(FName MobId, int32 ChainCommandId, TArray<FEndMobPrefabRandomAnimationExecuteItem> Items, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange) {
    return 0;
}

int32 AEndMobPrefabActor::AddRandom8AnimationWithLookAtExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion1, float Weight1, bool bAllowMotionCancel1, FName Motion2, float Weight2, bool bAllowMotionCancel2, FName Motion3, float Weight3, bool bAllowMotionCancel3, FName Motion4, float Weight4, bool bAllowMotionCancel4, FName Motion5, float Weight5, bool bAllowMotionCancel5, FName Motion6, float Weight6, bool bAllowMotionCancel6, FName Motion7, float Weight7, bool bAllowMotionCancel7, FName Motion8, float Weight8, bool bAllowMotionCancel8, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange) {
    return 0;
}

int32 AEndMobPrefabActor::AddRandom8AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion1, float Weight1, bool bAllowMotionCancel1, FName Motion2, float Weight2, bool bAllowMotionCancel2, FName Motion3, float Weight3, bool bAllowMotionCancel3, FName Motion4, float Weight4, bool bAllowMotionCancel4, FName Motion5, float Weight5, bool bAllowMotionCancel5, FName Motion6, float Weight6, bool bAllowMotionCancel6, FName Motion7, float Weight7, bool bAllowMotionCancel7, FName Motion8, float Weight8, bool bAllowMotionCancel8, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange) {
    return 0;
}

int32 AEndMobPrefabActor::AddRandom4AnimationWithLookAtExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion1, float Weight1, bool bAllowMotionCancel1, FName Motion2, float Weight2, bool bAllowMotionCancel2, FName Motion3, float Weight3, bool bAllowMotionCancel3, FName Motion4, float Weight4, bool bAllowMotionCancel4, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange) {
    return 0;
}

int32 AEndMobPrefabActor::AddRandom4AnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion1, float Weight1, bool bAllowMotionCancel1, FName Motion2, float Weight2, bool bAllowMotionCancel2, FName Motion3, float Weight3, bool bAllowMotionCancel3, FName Motion4, float Weight4, bool bAllowMotionCancel4, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange) {
    return 0;
}

int32 AEndMobPrefabActor::AddPlayingAnimationConditionCommand(FName MobId, int32 ChainCommandId, FName Motion0, FName Motion1, FName Motion2, FName Motion3) {
    return 0;
}

int32 AEndMobPrefabActor::AddPartyPositionConditionCommand(FName MobId, int32 ChainCommandId, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime, FName TargetName) {
    return 0;
}

int32 AEndMobPrefabActor::AddOnceConditionCommand(FName MobId, int32 ChainCommandId, bool bAllowReset) {
    return 0;
}

int32 AEndMobPrefabActor::AddMoveArroundExecuteCommand(FName MobId, int32 ChainCommandId, float MoveRadius, float RunRate, FVector2D MoveDistanceRange, FVector2D MoveWaitTimeRange, float MoveTimeOut, float CautionDistance) {
    return 0;
}

int32 AEndMobPrefabActor::AddLookAtStartExecuteCommand(FName MobId, int32 ChainCommandId, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway) {
    return 0;
}

int32 AEndMobPrefabActor::AddLookAtExecuteCommand(FName MobId, int32 ChainCommandId, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange) {
    return 0;
}

int32 AEndMobPrefabActor::AddLookAtEndExecuteCommand(FName MobId, int32 ChainCommandId) {
    return 0;
}

int32 AEndMobPrefabActor::AddEventUnbindMessageCommand(FName MobId, int32 ChainCommandId) {
    return 0;
}

int32 AEndMobPrefabActor::AddEventStateTriggerMessageCommand(FName MobId, int32 ChainCommandId, EEndMobPrefabStateTrigger Trigger) {
    return 0;
}

int32 AEndMobPrefabActor::AddEmptyConditionCommand(FName MobId, int32 ChainCommandId) {
    return 0;
}

int32 AEndMobPrefabActor::AddContactConditionCommand(FName MobId, int32 ChainCommandId, bool bForwardLeft, bool bForwardRight, bool bBackLeft, bool bBackRight, float ContinuationTime) {
    return 0;
}

int32 AEndMobPrefabActor::AddContactAnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName ForwardLeftMotion, FName ForwardRightMotion, FName BackLeftMotion, FName BackRightMotion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange, bool bAllowMotionCancel) {
    return 0;
}

int32 AEndMobPrefabActor::AddAutoReactionToPartyExecuteCommand(FName MobId, int32 ChainCommandId, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime, bool bFromCenter, FName TargetName, FName Motion, float BlendTime, FName ReplaceBaseMotion, FName OutMotion, float OutBlendTime, FName OutReplaceBaseMotion, bool bPlayMotionOnce) {
    return 0;
}

int32 AEndMobPrefabActor::AddAutoLookAtPartyExecuteCommand(FName MobId, int32 ChainCommandId, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime, bool bFromCenter, FName TargetName, bool bLookAway) {
    return 0;
}

int32 AEndMobPrefabActor::AddAutoLookAtActorExecuteCommand(FName MobId, int32 ChainCommandId, FName Actor0, FName Actor1, FName Actor2, FName Actor3, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime, bool bFromCenter) {
    return 0;
}

int32 AEndMobPrefabActor::AddAnimationWithLookAtExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FName LookAtTargetMob, float LookAtBlendRate, bool bLookAway, FVector2D CompleteTimeRange, bool bAllowMotionCancel) {
    return 0;
}

int32 AEndMobPrefabActor::AddAnimationExecuteCommand(FName MobId, int32 ChainCommandId, FName Motion, bool bLooping, float BlendTime, FName Layer, FName ReplaceBaseMotion, FName ReplaceBaseLookAtTarget, FVector2D CompleteTimeRange, bool bAllowMotionCancel) {
    return 0;
}

int32 AEndMobPrefabActor::AddAllowContactPropagateExecuteCommand(const TMap<FName, FName>& PropagateMotionTable, const TMap<FName, FName>& PropagateForwardLeftMotionTable, const TMap<FName, FName>& PropagateForawrdRightMotionTable, const TMap<FName, FName>& PropagateBackLeftMotionTable, const TMap<FName, FName>& PropagateBackRightMotionTable, FName MobId, int32 ChainCommandId, bool bAllowedDuringPlayMotion, FName ForwardLeftMotion, FName ForwardRightMotion, FName BackLeftMotion, FName BackRightMotion, float ContactMotionBlendTime, float PropagateMotionBlendTime, FName OutMotion, float OutBlendTime, FName OutReplaceBaseMotion) {
    return 0;
}

int32 AEndMobPrefabActor::AddAllowContactExecuteCommand(FName MobId, int32 ChainCommandId, bool bAllowedDuringPlayMotion, FName ForwardLeftMotion, FName ForwardRightMotion, FName BackLeftMotion, FName BackRightMotion) {
    return 0;
}

int32 AEndMobPrefabActor::AddActorPositionConditionCommand(FName MobId, int32 ChainCommandId, FName Actor0, FName Actor1, FName Actor2, FName Actor3, float DistanceThreshold, float AngleThreshold, float HeightThreshold, float ContinuationTime) {
    return 0;
}


