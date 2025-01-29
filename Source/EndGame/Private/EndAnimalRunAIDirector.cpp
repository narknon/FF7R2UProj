#include "EndAnimalRunAIDirector.h"
#include "Templates/SubclassOf.h"

AEndAnimalRunAIDirector::AEndAnimalRunAIDirector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->ShootableDistanceToBall = 250.00f;
    this->ShootableHeightToBall = 100.00f;
    this->ShootableBallSpeedLimitV = 150.00f;
    this->ShootableAngleCheckDistance = 200.00f;
    this->ShootableAngleCharacterToBall = 90.00f;
}

void AEndAnimalRunAIDirector::SetOverrideParameter(FName CharacterName, TSubclassOf<UEndAnimalRunAIParameterBase> OverrideParameterClass) {
}

void AEndAnimalRunAIDirector::SetLockTarget(FName CharacterName, ETeamType TeamType) {
}

void AEndAnimalRunAIDirector::SetAnimationPlayRate(FName CharacterName, float PlayRate) {
}

void AEndAnimalRunAIDirector::ResetOverrideParameter(FName CharacterName) {
}

void AEndAnimalRunAIDirector::ResetAnimationPlayRate(FName CharacterName) {
}

void AEndAnimalRunAIDirector::RequestChangeMode(ETeamType TeamType, EEndAnimalRunTeamMode Mode) {
}

void AEndAnimalRunAIDirector::RemoveAttachEffect(int32 HandleId) {
}







int32 AEndAnimalRunAIDirector::GetTeamRank(ETeamType TeamType) const {
    return 0;
}

EEndAnimalRunTeamMode AEndAnimalRunAIDirector::GetTeamMode(ETeamType TeamType) const {
    return EEndAnimalRunTeamMode::Default;
}

AEndCharacterBase* AEndAnimalRunAIDirector::GetRunWildAICharacter(FName CharacterName) const {
    return NULL;
}

void AEndAnimalRunAIDirector::ChangeDefaultParameter(FName CharacterName, TSubclassOf<UEndAnimalRunAIParameterBase> DefaultParameterClass) {
}

void AEndAnimalRunAIDirector::AddAttachEffect(FName EffectName, FName CharacterName, FName AttachSocketNam, int32& OutHandleId) {
}


