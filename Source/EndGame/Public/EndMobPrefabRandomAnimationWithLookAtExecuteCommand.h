#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabRandomAnimationExecuteCommand.h"
#include "EndMobPrefabRandomAnimationWithLookAtExecuteCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabRandomAnimationWithLookAtExecuteCommand : public UEndMobPrefabRandomAnimationExecuteCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LookAtTargetMob;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LookAtBlendRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLookAway;
    
    UEndMobPrefabRandomAnimationWithLookAtExecuteCommand();

};

