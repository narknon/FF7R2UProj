#include "EndCardGame3DBoard.h"

AEndCardGame3DBoard::AEndCardGame3DBoard(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MPC_Player_Status = 0;
    this->MPC_Player_LanePower1 = 0;
    this->MPC_Player_LanePower2 = 0;
    this->MPC_Player_LanePower3 = 0;
    this->MPC_Enemy_Status = 0;
    this->MPC_Enemy_LanePower1 = 0;
    this->MPC_Enemy_LanePower2 = 0;
    this->MPC_Enemy_LanePower3 = 0;
}

void AEndCardGame3DBoard::DebugTest() {
}


