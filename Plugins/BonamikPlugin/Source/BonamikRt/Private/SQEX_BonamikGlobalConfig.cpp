#include "SQEX_BonamikGlobalConfig.h"

USQEX_BonamikGlobalConfig::USQEX_BonamikGlobalConfig() {
    this->bEnableTickComponent = true;
    this->bDebugDrawBonamik = false;
    this->bEnableUpdate = true;
    this->bMultiThreadUpdate = true;
    this->bEnableSimulation = true;
    this->bEnableUpdateOverlaps = true;
    this->TimeStep = 0.03f;
    this->ExpectedFrameRate = 30.00f;
    this->MayaAnimationFrameRate = 30.00f;
    this->MayaSimulationFrameRate = 20.00f;
    this->WindSourceSpeedFactor = 100.00f;
    this->bTickWindWhenPaused = true;
    this->GameUnitsPerMeter = 100.00f;
    this->AmplifyLiftForEND2 = 1.00f;
    this->AmplifyDragForEND2 = 1.00f;
    this->DefaultWorldWindScale = 1.00f;
}


