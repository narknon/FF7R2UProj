#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabPositionConditionCommand.h"
#include "EndMobPrefabPartyPositionConditionCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabPartyPositionConditionCommand : public UEndMobPrefabPositionConditionCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetName;
    
    UEndMobPrefabPartyPositionConditionCommand();

};

