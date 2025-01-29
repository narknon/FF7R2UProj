#include "EndBattleTalkCharacterComponent.h"

UEndBattleTalkCharacterComponent::UEndBattleTalkCharacterComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

bool UEndBattleTalkCharacterComponent::OnNotifyWithAbility_Implementation(const FName& AnimName, const FName& SoundName, AEndCharacter* OwnerChara, AEndCharacter* targetChara, const FName& AbilityId, FEndDataObjectBattleAbilityAccessor dataObjectBattleAbility, bool bFinishBlow) const {
    return false;
}

bool UEndBattleTalkCharacterComponent::OnNotify_Implementation(const FName& AnimName, const FName& SoundName, AEndCharacter* OwnerChara) const {
    return false;
}


