#include "EndBattleCountAPI.h"

UEndBattleCountAPI::UEndBattleCountAPI() {
}

int32 UEndBattleCountAPI::GetBattleCountLogIntByBP(FName ownerCharaName, EEndBattleCountLogType Type, FName TargetCharaName, FName subTypeName, FName territoryID) {
    return 0;
}

float UEndBattleCountAPI::GetBattleCountLogFloatByBP(FName ownerCharaName, EEndBattleCountLogType Type, FName TargetCharaName, FName subTypeName, FName territoryID) {
    return 0.0f;
}

bool UEndBattleCountAPI::GetBattleCountLogBoolByBP(FName ownerCharaName, EEndBattleCountLogType Type, FName TargetCharaName, FName subTypeName, FName territoryID) {
    return false;
}


