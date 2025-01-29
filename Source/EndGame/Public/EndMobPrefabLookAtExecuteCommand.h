#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMobPrefabExecuteCommand.h"
#include "EndMobPrefabLookAtExecuteCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabLookAtExecuteCommand : public UEndMobPrefabExecuteCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LookAtTargetMob;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LookAtBlendRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLookAway;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D CompleteTimeRange;
    
    UEndMobPrefabLookAtExecuteCommand();

};

