#include "EndBTDecorator_CheckATBGauge.h"

UEndBTDecorator_CheckATBGauge::UEndBTDecorator_CheckATBGauge() {
    this->NodeName = TEXT("[End][AIPC]CheckATBGauge");
    this->Operator = EEndAiMathCmp::Equal;
    this->Gauge = 0;
}


