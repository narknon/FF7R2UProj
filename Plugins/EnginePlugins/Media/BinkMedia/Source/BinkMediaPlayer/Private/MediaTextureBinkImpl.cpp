#include "MediaTextureBinkImpl.h"

UMediaTextureBinkImpl::UMediaTextureBinkImpl() {
    this->AddressX = TA_Wrap;
    this->AddressY = TA_Wrap;
    this->MediaPlayer = NULL;
    this->tonemap = false;
    this->OutputNits = 10000.00f;
    this->Alpha = 1.00f;
    this->DecodeSRGB = false;
}


