#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabConditionCommand.h"
#include "EndMobPrefabOnceConditionCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabOnceConditionCommand : public UEndMobPrefabConditionCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float bAllowReset;
    
    UEndMobPrefabOnceConditionCommand();

};

