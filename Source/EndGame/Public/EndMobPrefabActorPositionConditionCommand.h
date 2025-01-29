#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabPositionConditionCommand.h"
#include "EndMobPrefabActorPositionConditionCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabActorPositionConditionCommand : public UEndMobPrefabPositionConditionCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ActorNames;
    
    UEndMobPrefabActorPositionConditionCommand();

};

