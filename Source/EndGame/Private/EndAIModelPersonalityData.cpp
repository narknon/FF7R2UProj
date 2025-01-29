#include "EndAIModelPersonalityData.h"

UEndAIModelPersonalityData::UEndAIModelPersonalityData() {
    this->InitialUpdatePriority = EEndAIUpdatePriority::Middle;
    this->PersonalType = EEndAIPersonalType::Mob;
    this->ExperienceSpeed = 10.00f;
    this->CautionCalmSpeed = -5.00f;
    this->RemoveRecognitionTime = 180.00f;
}


