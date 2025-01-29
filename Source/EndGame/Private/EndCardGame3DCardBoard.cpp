#include "EndCardGame3DCardBoard.h"

AEndCardGame3DCardBoard::AEndCardGame3DCardBoard(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CardIndex = 0;
    this->MPC_CardFrame = 0;
    this->BoardMoveTimer = 0.00f;
    this->DeckMoveTimer = 0.00f;
    this->bCardCheckVisible = false;
    this->bCursorVisible = false;
    this->bPredictBuffVisible = false;
    this->bPredictDebuffVisible = false;
    this->bPredictFadeOutVisible = false;
}


