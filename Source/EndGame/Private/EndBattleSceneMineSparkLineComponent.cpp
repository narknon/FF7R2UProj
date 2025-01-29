#include "EndBattleSceneMineSparkLineComponent.h"

UEndBattleSceneMineSparkLineComponent::UEndBattleSceneMineSparkLineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bAutoActivate = true;
    this->SparkLineDistance = 0.00f;
    this->SparkLineReleaseDistance = 0.00f;
}

void UEndBattleSceneMineSparkLineComponent::SetOverrideSparkLineDamageSourceID(FName DamageSourceID) {
}

void UEndBattleSceneMineSparkLineComponent::ResetOverrideSparkLineDamageSourceID() {
}


