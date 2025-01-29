#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabConditionCommand.h"
#include "EndMobPrefabContactConditionCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabContactConditionCommand : public UEndMobPrefabConditionCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForwardLeft;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForwardRight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bBackLeft;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bBackRight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ContinuationTime;
    
    UEndMobPrefabContactConditionCommand();

};

