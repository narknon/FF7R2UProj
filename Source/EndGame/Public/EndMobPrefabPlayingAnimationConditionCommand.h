#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabConditionCommand.h"
#include "EndMobPrefabPlayingAnimationConditionCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabPlayingAnimationConditionCommand : public UEndMobPrefabConditionCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> Motions;
    
    UEndMobPrefabPlayingAnimationConditionCommand();

};

