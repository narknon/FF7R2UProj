#include "SQEXSEADAutoSeMotionSoundFilter.h"

FSQEXSEADAutoSeMotionSoundFilter::FSQEXSEADAutoSeMotionSoundFilter() {
    this->bMSFilterFlag_FootStep = false;
    this->bMSFilterFlag_FootShuffle = false;
    this->bMSFilterFlag_Jump = false;
    this->bMSFilterFlag_Land = false;
    this->bMSFilterFlag_RustleArm = false;
    this->bMSFilterFlag_RustleHandWave = false;
    this->bMSFilterFlag_RustleFoot = false;
    this->bMSFilterFlag_RustleFootCrotch = false;
    this->bMSFilterFlag_RustleFootBend = false;
    this->bMSFilterFlag_WingFlap = false;
    this->bMSFilterFlag_Turn = false;
    this->bMSFilterFlag_Bow = false;
    this->bMSFilterFlag_HeadRot = false;
    this->bMSFilterFlag_SwingKnock = false;
    this->bMSFilterFlag_SwingRub = false;
    this->bMSFilterFlag_RagdollBounce = false;
    this->bMSFilterFlag_RagdollFricative = false;
}

