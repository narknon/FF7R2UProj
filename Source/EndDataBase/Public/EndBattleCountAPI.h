#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EEndBattleCountLogType.h"
#include "EndBattleCountAPI.generated.h"

UCLASS(Blueprintable)
class ENDDATABASE_API UEndBattleCountAPI : public UObject {
    GENERATED_BODY()
public:
    UEndBattleCountAPI();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetBattleCountLogIntByBP(FName ownerCharaName, EEndBattleCountLogType Type, FName TargetCharaName, FName subTypeName, FName territoryID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBattleCountLogFloatByBP(FName ownerCharaName, EEndBattleCountLogType Type, FName TargetCharaName, FName subTypeName, FName territoryID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool GetBattleCountLogBoolByBP(FName ownerCharaName, EEndBattleCountLogType Type, FName TargetCharaName, FName subTypeName, FName territoryID);
    
};

