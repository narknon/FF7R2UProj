#include "EndExtensionAIStateSetting.h"

FEndExtensionAIStateSetting::FEndExtensionAIStateSetting() {
    this->DoNothing = EEndExtensionAIStateDoNothing::NONE;
    this->ConnectEncount = EEndExtensionAIStateConnectEncount::NONE;
    this->Battle = EEndExtensionAIStateBattle::NONE;
    this->Stay = EEndExtensionAIStateStay::NONE;
    this->MoveTo = EEndExtensionAIStateMoveTo::NONE;
    this->Lead = EEndExtensionAIStateLead::NONE;
    this->Follow = EEndExtensionAIStateFollow::NONE;
    this->Wandering = EEndExtensionAIStateWandering::NONE;
    this->Animation = EEndExtensionAIStateAnimation::NONE;
    this->Unique = EEndExtensionAIStateUnique::NONE;
    this->Interest = EEndExtensionAIStateInterest::NONE;
    this->WildAnimal = EEndExtensionAIStateWildAnimal::NONE;
    this->BattleEvacuation = EEndExtensionAIStateBattleEvacuation::NONE;
    this->HintAnimal = EEndExtensionAIStateHintAnimal::NONE;
    this->FieldAction = EEndExtensionAIStateFieldAction::NONE;
}

