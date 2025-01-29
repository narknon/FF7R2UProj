#include "SQEX_KineDriverConnection.h"

FSQEX_KineDriverConnection::FSQEX_KineDriverConnection() {
    this->ConnectionType = ESQEX_KD_ConnectionType::ESQEX_KD_ConnectionType_Float;
    this->OtherSourceParamIndex = 0;
    this->OtherTargetParamIndex = 0;
    this->Coef = 0.00f;
}

