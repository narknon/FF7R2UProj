#include "EndEnvQueryTest_InRecognitionVolume.h"

UEndEnvQueryTest_InRecognitionVolume::UEndEnvQueryTest_InRecognitionVolume() {
    this->FilterType = EEnvTestFilterType::Match;
    this->ScoringEquation = EEnvTestScoreEquation::Constant;
    this->VolumeType = EEndAIRecognitionVolumeType::Common00;
    this->GroupId = -1;
}


