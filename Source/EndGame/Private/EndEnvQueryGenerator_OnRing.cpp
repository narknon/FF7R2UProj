#include "EndEnvQueryGenerator_OnRing.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEndEnvQueryGenerator_OnRing::UEndEnvQueryGenerator_OnRing() {
    this->bDefineArc = true;
    this->bDefineMaxRadius = false;
    this->bDefineMaxRadiusItemSpacing = false;
    this->bDefineMaxRadiusItemSpacingRatio = false;
    this->MaxRadiusItemSpacingRatio = 1.00f;
    this->bArcDirection3D = false;
    this->CircleCenter = UEnvQueryContext_Querier::StaticClass();
    this->RadiusMode = EEnvGeneratorOnRingRadiusMode::ContextCenter;
}


