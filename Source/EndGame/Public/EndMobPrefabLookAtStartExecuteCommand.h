#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabExecuteCommand.h"
#include "EndMobPrefabLookAtStartExecuteCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabLookAtStartExecuteCommand : public UEndMobPrefabExecuteCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LookAtTargetMob;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LookAtBlendRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLookAway;
    
    UEndMobPrefabLookAtStartExecuteCommand();

};

