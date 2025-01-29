#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabAnimationExecuteCommand.h"
#include "EndMobPrefabAnimationWithLookAtExecuteCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabAnimationWithLookAtExecuteCommand : public UEndMobPrefabAnimationExecuteCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LookAtTargetMob;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LookAtBlendRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLookAway;
    
    UEndMobPrefabAnimationWithLookAtExecuteCommand();

};

