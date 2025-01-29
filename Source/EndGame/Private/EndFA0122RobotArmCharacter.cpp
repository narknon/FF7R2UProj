#include "EndFA0122RobotArmCharacter.h"

AEndFA0122RobotArmCharacter::AEndFA0122RobotArmCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TurningSoundAsset = NULL;
    this->StopTurningSoundAsset = NULL;
    this->ElevatingSoundAsset = NULL;
    this->StopElevatingSoundAsset = NULL;
    this->EnvironmentHitSoundAsset = NULL;
    this->ContainerHitSoundAsset = NULL;
}


