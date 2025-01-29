#include "SQEX_BonamikSimpleLinkDesc.h"

FSQEX_BonamikSimpleLinkDesc::FSQEX_BonamikSimpleLinkDesc() {
    this->mStretchedStrength = 0.00f;
    this->mCompressedStrength = 0.00f;
    this->mLinkParentStrength = 0.00f;
    this->bIsBending = false;
    this->bEnableJointTwist = false;
    this->bEnableLengthAnimation = false;
}

