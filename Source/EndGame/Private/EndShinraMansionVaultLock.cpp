#include "EndShinraMansionVaultLock.h"

AEndShinraMansionVaultLock::AEndShinraMansionVaultLock(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InputInertia = 4.00f;
    this->DPadInputInterval = 0.40f;
    this->DPadInputInertia = 0.80f;
    this->CurrentInputPreventTime = 0.00f;
    this->DPadCurrentInputPreventTime = 0.00f;
    this->InputPreventTime = 0.20f;
    this->InputPreventMinTime = 0.05f;
    this->DPadInputPreventTime = 0.00f;
    this->InputChangePerRotate = 3.00f;
    this->MaxNumberInput = 60;
    this->MaxColNumber = 4;
    this->FirstColPassword = 10;
    this->FirstColInput = 0;
    this->SecondColPassword = 20;
    this->SecondColInput = 0;
    this->ThirdColPassword = 30;
    this->ThirdColInput = 0;
    this->FourthColPassword = 40;
    this->FourthColInput = 0;
    this->CurrentSelectedCol = 0;
    this->CurrentDialNumber = 0;
}


