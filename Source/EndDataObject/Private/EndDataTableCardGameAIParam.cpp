#include "EndDataTableCardGameAIParam.h"

FEndDataTableCardGameAIParam::FEndDataTableCardGameAIParam() {
    this->EnemyPowerQT = 0.00f;
    this->PlayerPowerQT = 0.00f;
    this->EnemyFlagQT = 0.00f;
    this->PlayerFlagQT = 0.00f;
    this->EnemySpecialQT = 0.00f;
    this->PlayerSpecialQT = 0.00f;
    this->EnemyCardConservationOneRoundQT = 0.00f;
    this->EnemyCardConservationTwoRoundQT = 0.00f;
    this->EnemyCardConservationThreeRoundQT = 0.00f;
    this->PlayerCardConservationOneRoundQT = 0.00f;
    this->PlayerCardConservationTwoRoundQT = 0.00f;
    this->PlayerCardConservationThreeRoundQT = 0.00f;
    this->SpecialPrediction = 0;
    this->EnemyPredictionTurn = 0;
    this->PlayerPredictionTurn = 0;
    this->NeedCanPutCount = 0;
    this->CanNotPutMinusValue = 0.00f;
    this->BuffInflNoCardQT = 0.00f;
    this->DebufInflNoCardQT = 0.00f;
    this->BuffInflNoActivateQT = 0.00f;
    this->DebufInflNoActivateQT = 0.00f;
}

