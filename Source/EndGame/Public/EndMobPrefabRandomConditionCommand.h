#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabConditionCommand.h"
#include "EndMobPrefabRandomConditionCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabRandomConditionCommand : public UEndMobPrefabConditionCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Rate;
    
    UEndMobPrefabRandomConditionCommand();

};

