#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMobPrefabConditionCommand.h"
#include "EndMobPrefabTimerConditionCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabTimerConditionCommand : public UEndMobPrefabConditionCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D WaitTimeRange;
    
    UEndMobPrefabTimerConditionCommand();

};

