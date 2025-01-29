#include "EndBattleAISummonBaseController.h"

AEndBattleAISummonBaseController::AEndBattleAISummonBaseController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->WarpMoveDistance = 1200.00f;
    this->UseWarpPointDistance = 600.00f;
    this->CoolDownDistance = 600.00f;
    this->EscortDistance = 600.00f;
    this->SightAngle = 60.00f;
    this->MaxDistanceFromOwner = 1500.00f;
    this->WarpMoveDistanceForBizarroSephiroth = 4500.00f;
}

void AEndBattleAISummonBaseController::WarpToCachedLocation() {
}

void AEndBattleAISummonBaseController::SetDrawPause(bool bDrawPause) {
}

void AEndBattleAISummonBaseController::SetAppear(bool bAppear) {
}

bool AEndBattleAISummonBaseController::RequestWarpTo(FVector WarpLocation) {
    return false;
}

void AEndBattleAISummonBaseController::RequestShowCutSceneAbilityName() {
}







void AEndBattleAISummonBaseController::OnAppearNotify() {
}



bool AEndBattleAISummonBaseController::IsUsedMoogleAbility() const {
    return false;
}

void AEndBattleAISummonBaseController::CreateDamageSourceByCurrentTargetBase(FName DamageSourceID) {
}

void AEndBattleAISummonBaseController::ChangeMyTarget(AEndCharacter* InCharacter) {
}


