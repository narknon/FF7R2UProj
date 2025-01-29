#include "NetDriverEOS.h"

UNetDriverEOS::UNetDriverEOS() : UIpNetDriver(FObjectInitializer::Get()) {
    this->ChannelDefinitions.AddDefaulted(3);
    this->bIsPassthrough = false;
    this->bIsUsingP2PSockets = false;
}


