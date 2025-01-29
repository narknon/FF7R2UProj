#include "EndAIReactionInfoCommand.h"

FEndAIReactionInfoCommand::FEndAIReactionInfoCommand() {
    this->CommandType = EEndBattleAbilityCommandType::None;
    this->PlayerType = EEndAIReactionPlayerType::All;
}

