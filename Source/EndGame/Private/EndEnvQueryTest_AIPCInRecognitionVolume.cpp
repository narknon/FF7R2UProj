#include "EndEnvQueryTest_AIPCInRecognitionVolume.h"

UEndEnvQueryTest_AIPCInRecognitionVolume::UEndEnvQueryTest_AIPCInRecognitionVolume() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->VolumeType = EEndAIRecognitionVolumeType::SafeArea;
}


